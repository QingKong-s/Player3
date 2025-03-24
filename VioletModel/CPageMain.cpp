﻿#include "pch.h"
#include "CWndMain.h"

LRESULT CPageMain::OnEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZE:
	{
		m_Lyt.Arrange(GetWidth(), GetHeight());
	}
	return 0;
	case WM_SETFONT:
		m_BTOpenFile.SetTextFormat(GetTextFormat());
		m_BTOpenFolder.SetTextFormat(GetTextFormat());
		return 0;
	case WM_CREATE:
	{
		constexpr MARGINS Mar{ .cxRightWidth = CxPageIntPadding };
		const auto pWnd = (CWndMain*)GetWnd();
		m_BTOpenFile.Create(L"打开文件", Dui::DES_VISIBLE, 0,
			0, 0, 140, 40, this, GetWnd());
		m_BTOpenFile.SetBitmap(pWnd->RealizeImg(GImg::File));
		m_Lyt.Add(&m_BTOpenFile, Mar, eck::LF_FIX);

		m_BTOpenFolder.Create(L"打开文件夹", Dui::DES_VISIBLE, 0,
			0, 0, 140, 40, this, GetWnd());
		m_BTOpenFolder.SetBitmap(pWnd->RealizeImg(GImg::Folder));
		m_BTOpenFolder.SetTextFormat(GetTextFormat());
		m_Lyt.Add(&m_BTOpenFolder, Mar, eck::LF_FIX);

		m_Lyt.Add(&m_Dummy, {}, eck::LF_FIX_HEIGHT | eck::LF_FILL_WIDTH, 1);

		m_LATest.Create(nullptr, Dui::DES_VISIBLE, 0,
			0, 0, 400, 160, this, GetWnd());
		m_LATest.SetOnlyBitmap(TRUE);
		m_LATest.SetBitmap(pWnd->RealizeImg(GImg::Test));
		//m_LATest.SetFullElem(TRUE);
		m_LATest.SetBkImgMode(eck::BkImgMode::Center);
		m_Lyt.Add(&m_LATest, Mar, eck::LF_FIX_WIDTH | eck::LF_FILL_HEIGHT);
	}
	break;
	case WM_DESTROY:
		break;
	}
	return __super::OnEvent(uMsg, wParam, lParam);
}