#include "pch.h"
#include "CPlayListMgr.h"

void CPlayListMgr::LoadList()
{
    auto rsPath{ eck::GetRunningPath() };
    rsPath.PushBack(L"\\List");
    auto FnCallback = [&](eck::CEnumFile::TDefInfo& e) noexcept
        {
            auto& List = *m_vPlayList.emplace_back(std::make_shared<CPlayList>()).pList;
            List.SetListFile(rsPath.ToStringView(),
                std::wstring_view{ e.FileName,e.FileNameLength / sizeof(WCHAR) });
            List.ImMarkNeedInit();
        };
    eck::CEnumFile ef{};
    ef.Open(rsPath.Data());
    ef.Enumerate(FnCallback, EckStrAndLen(L"*.VltList"));
    ef.Enumerate(FnCallback, EckStrAndLen(L"*.PNList"));
    ef.Enumerate(FnCallback, EckStrAndLen(L"*.QKList"));
}

std::shared_ptr<CPlayList> CPlayListMgr::Add()
{
    return m_vPlayList.emplace_back(std::make_shared<CPlayList>()).pList;
}

void CPlayListMgr::InvalidateImageList()
{
    for (auto& e : m_vPlayList)
    {
        e.pImageList.Clear();
        e.pList->InvalidateImage();
    }
}