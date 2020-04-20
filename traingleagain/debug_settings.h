#ifndef _DEBUG_SETTINGS_H_
#define _DEBUG_SETTINGS_H_

//the below flag is for runtime checks of debug status in code, instead of compile time checks
typedef enum
{
	RT_RELEASE = 0,
	RT_DEBUG = 1
}RtDebug;
#ifdef DEBUG
static const RtDebug RT_DEBUG_FLAG = RT_DEBUG;
#else
static const RtDebug RT_DEBUG_FLAG = RT_RELEASE;
#endif // DEBUG

#endif // !_DEBUG_SETTINGS_H_

