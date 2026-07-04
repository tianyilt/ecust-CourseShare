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

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_00000000003369484941_3356040082_init();
    work_m_00000000004291708365_4273201688_init();
    work_m_00000000003911670558_0864829514_init();
    work_m_00000000002575878488_3683860065_init();
    work_m_00000000002413819413_1606217436_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000002413819413_1606217436");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
