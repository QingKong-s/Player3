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