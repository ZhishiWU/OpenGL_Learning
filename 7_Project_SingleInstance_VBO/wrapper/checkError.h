#pragma once

void checkError(void);

#ifdef DEBUG
	#define GL_CHECK_ERROR(func); func;checkError();
#else
	#define GL_CHECK_ERROR(func); func;
#endif // DEBUG
