/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "D:/test/final/Key_Input.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {1U, 0U};
static unsigned int ng3[] = {2U, 0U};
static unsigned int ng4[] = {3U, 0U};



static void Always_26_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;

LAB0:    t1 = (t0 + 4032U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(26, ng0);
    t2 = (t0 + 4848);
    *((int *)t2) = 1;
    t3 = (t0 + 4064);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(26, ng0);

LAB5:    xsi_set_current_line(27, ng0);
    t4 = (t0 + 1592U);
    t5 = *((char **)t4);
    t4 = (t0 + 2312);
    xsi_vlogvar_assign_value(t4, t5, 0, 0, 1);
    goto LAB2;

}

static void Always_30_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    int t13;
    char *t14;
    char *t15;

LAB0:    t1 = (t0 + 4280U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(30, ng0);
    t2 = (t0 + 4864);
    *((int *)t2) = 1;
    t3 = (t0 + 4312);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(31, ng0);

LAB5:    xsi_set_current_line(32, ng0);
    t4 = (t0 + 1592U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(32, ng0);

LAB9:    xsi_set_current_line(33, ng0);
    t11 = (t0 + 1912U);
    t12 = *((char **)t11);

LAB10:    t11 = ((char*)((ng1)));
    t13 = xsi_vlog_unsigned_case_xcompare(t12, 2, t11, 2);
    if (t13 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng2)));
    t13 = xsi_vlog_unsigned_case_xcompare(t12, 2, t2, 2);
    if (t13 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng3)));
    t13 = xsi_vlog_unsigned_case_xcompare(t12, 2, t2, 2);
    if (t13 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng4)));
    t13 = xsi_vlog_unsigned_case_xcompare(t12, 2, t2, 2);
    if (t13 == 1)
        goto LAB17;

LAB18:
LAB19:    goto LAB8;

LAB11:    xsi_set_current_line(34, ng0);
    t14 = (t0 + 1752U);
    t15 = *((char **)t14);
    t14 = (t0 + 2472);
    xsi_vlogvar_wait_assign_value(t14, t15, 0, 0, 4, 0LL);
    goto LAB19;

LAB13:    xsi_set_current_line(35, ng0);
    t3 = (t0 + 1752U);
    t4 = *((char **)t3);
    t3 = (t0 + 2632);
    xsi_vlogvar_wait_assign_value(t3, t4, 0, 0, 4, 0LL);
    goto LAB19;

LAB15:    xsi_set_current_line(36, ng0);
    t3 = (t0 + 1752U);
    t4 = *((char **)t3);
    t3 = (t0 + 2792);
    xsi_vlogvar_wait_assign_value(t3, t4, 0, 0, 4, 0LL);
    goto LAB19;

LAB17:    xsi_set_current_line(37, ng0);
    t3 = (t0 + 1752U);
    t4 = *((char **)t3);
    t3 = (t0 + 2952);
    xsi_vlogvar_wait_assign_value(t3, t4, 0, 0, 4, 0LL);
    goto LAB19;

}

static void Always_42_2(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;

LAB0:    t1 = (t0 + 4528U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(42, ng0);
    t2 = (t0 + 4880);
    *((int *)t2) = 1;
    t3 = (t0 + 4560);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(42, ng0);

LAB5:    xsi_set_current_line(43, ng0);
    t4 = (t0 + 1912U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_xcompare(t5, 2, t4, 2);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng2)));
    t6 = xsi_vlog_unsigned_case_xcompare(t5, 2, t2, 2);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_xcompare(t5, 2, t2, 2);
    if (t6 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_xcompare(t5, 2, t2, 2);
    if (t6 == 1)
        goto LAB13;

LAB14:
LAB15:    goto LAB2;

LAB7:    xsi_set_current_line(44, ng0);
    t7 = (t0 + 2472);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    t10 = (t0 + 3112);
    xsi_vlogvar_assign_value(t10, t9, 0, 0, 4);
    goto LAB15;

LAB9:    xsi_set_current_line(45, ng0);
    t3 = (t0 + 2632);
    t4 = (t3 + 56U);
    t7 = *((char **)t4);
    t8 = (t0 + 3112);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 4);
    goto LAB15;

LAB11:    xsi_set_current_line(46, ng0);
    t3 = (t0 + 2792);
    t4 = (t3 + 56U);
    t7 = *((char **)t4);
    t8 = (t0 + 3112);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 4);
    goto LAB15;

LAB13:    xsi_set_current_line(47, ng0);
    t3 = (t0 + 2952);
    t4 = (t3 + 56U);
    t7 = *((char **)t4);
    t8 = (t0 + 3112);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 4);
    goto LAB15;

}


extern void work_m_00000000003911670558_0864829514_init()
{
	static char *pe[] = {(void *)Always_26_0,(void *)Always_30_1,(void *)Always_42_2};
	xsi_register_didat("work_m_00000000003911670558_0864829514", "isim/t0_isim_beh.exe.sim/work/m_00000000003911670558_0864829514.didat");
	xsi_register_executes(pe);
}
