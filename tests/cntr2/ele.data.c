#include "memheap/heap_global.h"

#include "ele.data.h"

address int_repo[TD_NUM];
address longint_repo[TD_NUM];
address float_repo[TD_NUM];
address double_repo[TD_NUM];
address char_repo[TD_NUM];
address string_repo[TD_NUM];

static int     *int_td_repo;
static longint *longint_td_repo;
static float   *float_td_repo;
static double  *double_td_repo;
static char    *char_td_repo;
static char*   *string_td_repo;

/* same as repo to check if the content of repo is destroyed */
static int     *int_td_repo_bak;
static longint *longint_td_repo_bak;
static float   *float_td_repo_bak;
static double  *double_td_repo_bak;
static char    *char_td_repo_bak;
static char*   *string_td_repo_bak;

static bool td_repo_initialized = false;
void td_repo_init() {
	int i;
	if (td_repo_initialized == true) 
		return;

	td_repo_initialized = true;

	int_td_repo = (int*)halloc(TD_NUM * sizeof(int));
	longint_td_repo = (longint*)halloc(TD_NUM * sizeof(longint));
	float_td_repo = (float*)halloc(TD_NUM * sizeof(float));
	double_td_repo = (double*)halloc(TD_NUM * sizeof(double));
	char_td_repo = (char*)halloc(TD_NUM * sizeof(char));
	string_td_repo = (char**)halloc(TD_NUM * sizeof(char*));

	int_td_repo_bak = (int*)halloc(TD_NUM * sizeof(int));
	longint_td_repo_bak = (longint*)halloc(TD_NUM * sizeof(longint));
	float_td_repo_bak = (float*)halloc(TD_NUM * sizeof(float));
	double_td_repo_bak = (double*)halloc(TD_NUM * sizeof(double));
	char_td_repo_bak = (char*)halloc(TD_NUM * sizeof(char));
	string_td_repo_bak = (char**)halloc(TD_NUM * sizeof(char*));

	for (i = 0; i < TD_NUM; i ++) {
		int_td_repo[i] = i;
		longint_td_repo[i] = (longint)i + INT_MAX;
		float_td_repo[i] = (float)i;
		double_td_repo[i] = (double)i;
		char_td_repo[i] = (char)i;

		int_td_repo_bak[i] = i;
		longint_td_repo_bak[i] = (longint)i + INT_MAX;
		float_td_repo_bak[i] = (float)i;
		double_td_repo_bak[i] = (double)i;
		char_td_repo_bak[i] = (char)i;
		{
			int j = 0;
			int str_len = rand() % TD_STRING_MAX_LENGTH + 1;
			string_td_repo[i] = (char*)halloc((str_len + 1) * sizeof(char*));
			string_td_repo_bak[i] = (char*)halloc((str_len + 1) * sizeof(char*));
			for (j = 0; j < str_len; j ++) {
				int rd = ((rand()%127+127)%127+ 1);
				char x = (char)rd;
				string_td_repo[i][j] = x;
				string_td_repo_bak[i][j] = string_td_repo[i][j];
			}
			string_td_repo[i][str_len] = '\0';
			string_td_repo_bak[i][str_len] = '\0';
		}

		int_repo[i]     = &int_td_repo[i];
		longint_repo[i] = &longint_td_repo[i];
		float_repo[i]   = &float_td_repo[i];
		double_repo[i]  = &double_td_repo[i];
		char_repo[i]    = &char_td_repo[i];
		string_repo[i]  = string_td_repo[i];
	}
}
void td_repo_deinit() {
	int i;
	if (td_repo_initialized == false) 
		return;

	td_repo_initialized = false;

	hfree(int_td_repo);
	hfree(longint_td_repo);
	hfree(float_td_repo);
	hfree(double_td_repo);
	hfree(char_td_repo);

	hfree(int_td_repo_bak);
	hfree(longint_td_repo_bak);
	hfree(float_td_repo_bak);
	hfree(double_td_repo_bak);
	hfree(char_td_repo_bak);
	for (i = 0; i < TD_NUM; i ++) {
		hfree(string_td_repo[i]);
		hfree(string_td_repo_bak[i]);
	}
	hfree(string_td_repo);
	hfree(string_td_repo_bak);
}
