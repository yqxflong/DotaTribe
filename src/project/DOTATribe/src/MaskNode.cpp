#include "../include/MaskNode.h"

void MaskNode::setViewData(UIViewData * data)
{
	viewData.alpha_ = data->alpha_;
	viewData.anchorx_ = data->anchorx_;
	viewData.anchory_ = data->anchory_;
	viewData.colorB_ = data->colorB_;
	viewData.colorG_ = data->colorG_;
	viewData.colorR_ = data->colorR_;
	strcpy(viewData.filepath_, data->filepath_);
	strcpy(viewData.filepath2_, data->filepath2_);
	strcpy(viewData.filepath3_, data->filepath3_);
	strcpy(viewData.fontname_, data->fontname_);
	viewData.fontsize_ = data->fontsize_;
	viewData.height_ = data->height_;
	viewData.width_ = data->width_;
	viewData.idx_ = data->idx_;
	viewData.posx_ = data->posx_;
	viewData.posy_ = data->posy_;
	viewData.zorder_ = data->zorder_;
	viewData.labelstring_=data->labelstring_;
	viewData.scale_ = data->scale_;
	viewData.hide_ = data->hide_;
	viewData.rotation_ = data->rotation_;
	viewData.m_nFontStyleID=data->m_nFontStyleID;
	viewData.soundid_ = data->soundid_;
	viewData.touchpriority_=data->touchpriority_;
	viewData.swallow_=data->swallow_;
}
//
const UIViewData & MaskNode::GetViewData()
{
	return viewData;
}
 
UIViewData *   MaskNode::GetViewPData()
{
	return &viewData;
}