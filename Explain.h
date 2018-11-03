#ifndef _EXPLAIN_H_
#define _EXPLAIN_H_

enum EX_PAGE
{
	EX_PAGE_1,
	EX_PAGE_2,
	EX_PAGE_MAX
};

void InitExplain(void);
void UninitExplain(void);
void UpdateExplain(void);
void DrawExplain(void);

#endif // !_EXPLAIN_H_
