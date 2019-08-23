#ifndef  _DOTATRIBE_HTTPTYPER_H_
#define  _DOTATRIBE_HTTPTYPER_H_


enum HTTPTyper
{
	_TYPED_PACKET_C2S_SERVERLIST_ = 104,							//c->s请求服务器列表		
	_TYPED_PACKET_S2C_SERVERLIST_ = 105,							//s->c服务器列表返回
	_TYPED_PACKET_C2S_VERSIONCHECK_ = 207,						//c - s,请求版本信息
	_TYPED_PACKET_S2C_VERSIONCHECK_ = 208,						//s - c,返回版本信息
	_TYPED_HTTP_C2S_NOTICEBOX_GATEWAY_ = 213,					//c->s,请求网关公告
	_TYPED_HTTP_S2C_NOTICEBOX_GATEWAY_ = 214,					//s->c,返回网关公告

};

#endif
