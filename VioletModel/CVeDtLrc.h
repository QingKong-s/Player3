#pragma once
struct NM_DTL_GET_TIME : Dui::DUINMHDR
{
    float fTime;
};

class CVeDtLrc : public Dui::CElem, public eck::CFixedTimeLine
{
public:
    constexpr static int c_InvalidCacheIdx = std::numeric_limits<int>::min();
private:
    enum : size_t
    {
        BriMain,
        BriTrans,
        BriMainHiLight,
        BriTransHiLight,
        BriBorder,
        BriShadow,

        BriMax
    };

    Lyric::CLyric* m_pLrc{};
    int m_idxCurr{ -1 };
public:
    LRESULT OnEvent(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

    void TlTick(int iMs) override;
    BOOL TlIsValid() override { return FALSE; }

    HRESULT LrcSetCurrentLine(int idx);
    void LrcSetEmptyText(std::wstring_view svEmptyText);

    void SetTextFormatTrans(IDWriteTextFormat* pTf);
    EckInlineNdCe auto GetTextFormatTrans() const { return (IDWriteTextFormat*)0; }

    void SetLyric(Lyric::CLyric* pLrc);
    EckInlineNdCe auto GetLyric() const { return m_pLrc; }
};