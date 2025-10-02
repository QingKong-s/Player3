﻿#pragma once
class CPlayList
{
    friend class CPlayer;
    friend class CPlayListMgr;
public:
    struct GROUPIDX
    {
        int idxGroup;
        int idxItem;
    };
private:
    struct ITEM
    {
        eck::CRefStrW rsName{};		// 名称
        eck::CRefStrW rsFile{};		// 文件路径

        eck::CRefStrW rsTitle{};	// 标题
        eck::CRefStrW rsArtist{};	// 艺术家
        eck::CRefStrW rsAlbum{};	// 唱片集
        eck::CRefStrW rsGenre{};	// 流派

        PLDATA s{};
        int idxSortMapping{ -1 };	// 【排序时用】映射到的项
        int idxIl{ 0 };				// 图像列表索引，供UI使用
    };

    struct GROUPSUB
    {
        int idxFlat;
    };
    struct GROUP
    {
        eck::CRefStrW rsName{};
        std::vector<GROUPSUB> vItem{};
    };

    eck::CRefStrW m_rsListFile{};		// 对应列表文件路径
    eck::CRefStrW m_rsName{};			// 列表名称

    std::vector<ITEM> m_vFlat{};
    std::vector<GROUP> m_vGroup{};

    std::vector<int> m_vSearchResult{};	// 搜索结果，存储平面列表索引

    int m_idxCurrFlat{};
    int m_idxCurrGroup{};
    int m_idxCurrGroupItem{};

    BITBOOL m_bGroup : 1{};
    BITBOOL m_bSort : 1{};
    BITBOOL m_bNeedInit : 1{};
    PlType m_eType{};

    int m_cTaskRef{};


    void ImFixGroupIndex(int idxFlatBegin, int nDelta);

    void ImMarkNeedInit() noexcept { m_bNeedInit = TRUE; }
public:
    void SetListFile(std::wstring_view svPath, std::wstring_view svFileName);
    void SetName(std::wstring_view svName) { m_rsName = svName; }
    EckInlineNdCe auto& GetName() const noexcept { return m_rsName; }

    void ImReserve(int cItem) { m_vFlat.reserve(cItem); }
    void ImReserveIncrement(int cItem) { m_vFlat.reserve(m_vFlat.size() + cItem); }

    void ImEnsureLoaded();

    EckInlineNdCe auto& FlAtAbs(int idx) noexcept { return m_vFlat[idx]; }
    EckInlineNdCe ITEM& FlAt(int idx) noexcept { return FlSchIsActive() ? FlAtAbs(FlSchAt(idx)) : FlAtAbs(idx); }

    /// <summary>
    /// 插入项目。
    /// 主操作列表为平面列表
    /// </summary>
    /// <param name="rsFile">文件全路径</param>
    /// <param name="idx">插入位置，-1表示末尾</param>
    /// <returns>索引</returns>
    int FlInsert(const eck::CRefStrW& rsFile, int idx = -1);
    int FlInsertEmpty(int idx = -1);

    EckInlineNdCe int FlGetCount() const noexcept { return (int)m_vFlat.size(); }

    void FlSchDoSearch(std::wstring_view svKeyWord);
    EckInlineNdCe int FlSchGetCount() const noexcept { return (int)m_vSearchResult.size(); }
    EckInlineNdCe BOOL FlSchIsActive() const noexcept { return !m_vSearchResult.empty(); }
    EckInlineNdCe int FlSchAt(int idx) noexcept { return m_vSearchResult[idx]; }
    EckInlineCe void FlSchCancel() noexcept { m_vSearchResult.clear(); }

    EckInlineNdCe auto& GrAtGroup(int idxGroup) noexcept { return m_vGroup[idxGroup]; }
    EckInlineNdCe auto& GrAt(int idxGroup, int idxItem) noexcept { return m_vFlat[m_vGroup[idxGroup].vItem[idxItem].idxFlat]; }

    /// <summary>
    /// 插入组
    /// </summary>
    /// <param name="rsName">组名</param>
    /// <param name="idx">插入位置，-1表示末尾</param>
    /// <returns>组索引</returns>
    int GrInsertGroup(const eck::CRefStrW& rsName, int idx = -1);

    /// <summary>
    /// 插入项目。
    /// 主操作列表为分组列表
    /// </summary>
    /// <param name="rsFile">文件全路径</param>
    /// <param name="idxItem">项目在组中的索引，-1表示末尾</param>
    /// <param name="idxGroup">所在组的索引，-1表示新建组</param>
    /// <returns></returns>
    GROUPIDX GrInsert(const eck::CRefStrW& rsFile, int idxItem = -1, int idxGroup = -1);

    EckInlineNdCe int GrGetGroupCount() const noexcept { return (int)m_vGroup.size(); }

    BOOL IsSelectedByPlayer() noexcept;

    // ---下列方法仅供播放器使用---

    EckInlineCe void PlySetCurrentItem(int idx) noexcept { m_idxCurrFlat = idx; }
    EckInlineCe void PlySetCurrentItem(int idxGroup, int idxItem) noexcept
    {
        EckAssert((idxGroup < 0) ? (idxItem < 0) : TRUE);
        m_idxCurrGroup = idxGroup;
        m_idxCurrGroupItem = idxItem;
    }
    EckInlineNdCe int PlyGetCurrentItem() const noexcept { return m_idxCurrFlat; }
    EckInlineNdCe int PlyGetCurrentItem(_Out_ int& idxGroup) const noexcept
    {
        idxGroup = m_idxCurrGroup;
        return m_idxCurrGroupItem;
    }
    // -------------------------

    EckInlineCe void EnableGroup(BOOL b) noexcept { m_bGroup = b; }
    EckInlineNdCe BOOL IsGroupEnabled() const noexcept { return m_bGroup; }

    HRESULT InitFromListFile(PCWSTR pszFile);

    // 下列函数必须在UI线程调用

    EckInlineNd BOOL TskIsRunning() const noexcept { return !!m_cTaskRef; }
    EckInlineCe void TskIncRef() noexcept { ++m_cTaskRef; }
    EckInlineCe void TskDecRef() noexcept { --m_cTaskRef; }

    void InvalidateImage();
};