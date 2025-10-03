#pragma once
struct LRD_INIT
{
    ID2D1DeviceContext* pD2DContext{};
    ID3D11DeviceContext* pD3DContext{};
};

struct LRD_TEXT_METRICS
{
    float cxMain{};
    float cyMain{};
    float cxTrans{};
    float cyTrans{};
};

enum : BYTE
{
    LRIF_NONE = 0,
    LRIF_AN_SEL_BKG = 1 << 0,
    LRIF_PREV_AN = 1 << 1,
    LRIF_CURR_AN = 1 << 2,
    LRIF_SCROLL_EXPAND = 1 << 3,
};
struct LRD_DRAW
{
    int idx;

    BYTE uFlags;			// LRIF_*
    eck::Align eAlignH;
    Dui::State eState;      // ����״̬����ΪState::None��ʾ�����Ʊ���

    float x;
    float y;
    float cx;
    float cy;

    float fScale;           // ��ǰ���ţ����ڳ������������Ϊ1
    float kAnSelBkg;		// 0~1��ָ��LRIF_AN_SEL_BKGʱ��Ч
    float kScrollExpand;	// 0~1��ָ��LRIF_SCROLL_EXPANDʱ��Ч
};

struct LRD_EMTRY_TEXT
{
    std::wstring_view svText;
};

class CLyricRendererBase : public eck::CRefObj<CLyricRendererBase>
{
public:
    enum : size_t
    {
        CriNormal,
        CriHiLight,
        CriMax
    };
protected:
    ComPtr<IDWriteTextFormat> m_pTfMain{};
    ComPtr<IDWriteTextFormat> m_pTfTrans{};

    ComPtr<Dui::ITheme> m_pTheme{};

    D2D1_COLOR_F m_Color[CriMax]{};

    float m_cxView{};
    float m_cyView{};
    float m_fMaxScale{ 1.1f };      // ��ǰ��Ŀ��������ű���
    float m_cxyLineMargin{ 14.f };  // ��Ŀ�ı���߿���
    float m_dMainToTrans{ 5.f };    // �����뷭����

    BOOLEAN m_bTopBtmFade{};		// ָʾ�Ƿ����ö����͵ײ�����
public:
    virtual ~CLyricRendererBase() = default;

    void SetTheme(Dui::ITheme* pTheme) { m_pTheme = pTheme; }
    void SetTextFormatMain(IDWriteTextFormat* pTf) { m_pTfMain = pTf; }
    void SetTextFormatTrans(IDWriteTextFormat* pTf) { m_pTfTrans = pTf; }

    void SetColor(size_t idx, const D2D1_COLOR_F& cr) { m_Color[idx] = cr; }
    void SetColor(_In_reads_(CriMax) const D2D1_COLOR_F* pcr)
    {
        for (size_t i = 0; i < CriMax; ++i)
            m_Color[i] = pcr[i];
    }

    void SetMaxScale(float f) { m_fMaxScale = f; }
    float GetMaxScale() const { return m_fMaxScale; }
    void SetItemMargin(float f) { m_cxyLineMargin = f; }
    float GetItemMargin() const { return m_cxyLineMargin; }
    void SetMainToTransDistance(float f) { m_dMainToTrans = f; }
    float GetMainToTransDistance() const { return m_dMainToTrans; }

    virtual HRESULT LrInit(const LRD_INIT& Opt) = 0;
    virtual void LrBeginDraw() = 0;
    virtual void LrEndDraw() = 0;
    virtual void LrItmSetCount(int cItems) = 0;
    virtual HRESULT LrItmUpdateText(int idx, const Lyric::Line& Line,
        _Out_ LRD_TEXT_METRICS& Met) = 0;
    virtual void LrItmDraw(const LRD_DRAW& Opt) = 0;
    virtual HRESULT LrUpdateEmptyText(const LRD_EMTRY_TEXT& Opt) = 0;
    virtual void LrSetViewSize(float cx, float cy) = 0;
    virtual void LrDpiChanged(float fNewDpi) = 0;
    virtual void LrInvalidate() = 0;
};