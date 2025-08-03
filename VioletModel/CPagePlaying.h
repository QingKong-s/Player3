﻿#pragma once
#include "CVeCover.h"
#include "CVeLrc.h"
#include "CApp.h"

// CWndMain负责更新该元素的图片
class CPagePlaying : public Dui::CElem
{
	friend class CWndMain;
private:
	CVeCover m_Cover{};
	CVeLrc m_Lrc{};
	Dui::CButton m_BTBack{};
	Dui::CLabel m_LATitle{};
	Dui::CLabel m_LAAlbum{};
	Dui::CLabel m_LAArtist{};

	ID2D1Bitmap1* m_pBmpCover{};
	ID2D1Bitmap1* m_pBmpBlurredCover{};
	ID2D1SolidColorBrush* m_pBrBkg{};

	void UpdateBlurredCover();

	void OnPlayEvent(const PLAY_EVT_PARAM& e);
public:
	LRESULT OnEvent(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	void SetLabelTextFormatTitle(IDWriteTextFormat* pTf)
	{
		m_LATitle.SetTextFormat(pTf);
	}

	void SetLabelTextFormat(IDWriteTextFormat* pTf)
	{
		m_LAAlbum.SetTextFormat(pTf);
		m_LAArtist.SetTextFormat(pTf);
	}
};