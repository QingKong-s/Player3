﻿#pragma once
class CVeVolumeBar : public Dui::CElem
{
private:
    Dui::CLabel m_LAVol{};
    Dui::CTrackBar m_TrackBar{};

    ID2D1SolidColorBrush* m_pBrush{};
    Dui::CCompositorPageAn m_PageAn{};
    eck::CEasingCurve m_ecShowing{};

    BOOL m_bShow{};
public:
    LRESULT OnEvent(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

    void ShowAnimation();

    void OnVolumeChanged(float fVol);
};