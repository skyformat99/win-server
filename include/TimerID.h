#ifndef __TIMER_ID__
#define __TIMER_ID__

enum ServerTimerID
{
	/*************************db**********************************/
	timer_db_begin = 1,


	timer_db_end = 100,
	/*************************normal**********************************/
	timer_server_normal_begin = 101,
	timer_delay_remove_player = 102,

	timer_server_normal_end = 500,
	/*************************lua**********************************/
	timer_lua_begin = 501,
	timer_lua_1_minute = 502,    //lua 1���Ӷ�ʱ
	timer_lua_10_minute = 503,   //lua 10���Ӷ�ʱ
	timer_lua_1_hour = 504,      //lua 1Сʱ��ʱ

	timer_lua_end = 520,

    timer_generate_begin = 100000000, //timerID��0ʱ�Զ����ɵ�timerID��Сֵ
	timer_generate_lua_begin = timer_generate_begin + 1000000,//lua�ű�:timerID��0ʱ�Զ����ɵ�timerID��Сֵ
};

enum DistriServerTimerID
{

};

enum DistriClientTimerID
{
    
};

#endif