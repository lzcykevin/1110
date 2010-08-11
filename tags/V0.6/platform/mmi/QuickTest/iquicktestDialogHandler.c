/*==============================================================================
// 文件：
//        iquicktestDialogHandler.c
//        版权所有(c) 2007 Anylook
//
// 文件说明：
//
// 创建日期：2007-11-13
// 作者：Gemsea
// 当前版本：Draft
==============================================================================*/
/*==============================================================================
修改历史记录：
时       间      修 改 人     修改内容、位置及原因
-----------      ----------     -----------------------------------------------
08-01-10          陈喜玲      实现快速测试的基本功能
07-11-13                初始版本
==============================================================================*/


/*==============================================================================
                                 本文件包含的外部文件
==============================================================================*/
#include "iquicktest_priv.h"

#ifndef WIN32
#if defined( FEATURE_FM_RADIO)
    #include "fm_radio.h"
#endif
#endif
#define RGBA_BLACK             MAKE_RGBA(0,0,0,255)

/*==============================================================================
                                 宏定义和常数
==============================================================================*/
// 关闭对话框宏
#define CLOSE_DIALOG(DlgRet)  {    \
                                     pMe->m_eDlgRet = DlgRet; \
                                     (void) ISHELL_EndDialog(pMe->m_pShell);  \
                                 }
/*==============================================================================
                                 类型定义
==============================================================================*/


/*==============================================================================
                                 函数声明
==============================================================================*/
// 对话框 IDD_MAINMENU 事件处理函数
static boolean  QuickTest_MainMenuHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
);

//对话框IDD_KEYTEST事件处理函数
static boolean  QuickTest_KeyTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
);

//对话框IDD_YAMAHATEST事件处理函数
static boolean  QuickTest_YAMAHATestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
);

//对话框IDD_VIBRATETEST事件处理函数
static boolean  QuickTest_VibrateTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
);

//对话框IDD_BACKLIGHTTEST事件处理函数
static boolean  QuickTest_BackLightTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
);

static boolean  QuickTest_FlipTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
); 

//对话框IDD_FMTEST事件处理函数
#if defined( FEATURE_FM_RADIO)
static boolean  QuickTest_FMTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
);
#endif

//对话框IDD_SDTEST事件处理函数
static boolean  QuickTest_SDTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
);

//对话框IDD_VERTEST事件处理函数
static boolean  QuickTest_VERTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
);

//对话框IDD_LCDTEST事件处理函数
static boolean  QuickTest_LCDTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
);

#ifdef FEATURE_TOUCHPANEL
//对话框IDD_TOUCHSCREENTEST事件处理函数
static boolean  QuickTest_TouchScreenTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
);
#endif // FEATURE_TOUCHPANEL

static boolean  QuickTest_CallHandler(CQuickTest *pMe,
                                      AEEEvent eCode,
                                      uint16 wParam,
                                      uint32 dwParam
);

//对话框IDD_RESTORE_FACTORY事件处理函数
static boolean  QuickTest_RestoreFactory_Handler(CQuickTest *pMe,
                                      AEEEvent eCode,
                                      uint16 wParam,
                                      uint32 dwParam
);

static void QuickTest_Vibrate(CQuickTest *pMe);
static void QuickTest_Ringer(CQuickTest *pMe);
static void quicktest_ChangeColor(void *pme);
static void quicktest_DrawSevenColor(CQuickTest *pme);

static void quicktest_mic_receiver_Loopback(CQuickTest *pMe);
#ifndef WIN32
extern qdsp_cmd_isr_func_type qdsp_cmd_isr_table[QDSP_ISR_MAX];
extern void qdsp_cmd_set_isr ( qdsp_cmd_isr_func_type isr_ptr);
extern void      iquicktest_mic_receiver_loopback_isr ( void );
#endif
extern boolean   IsRunAsUIMVersion(void);
#if defined( FEATURE_FM_RADIO)
#define LOWEST_BAND_FREQ 87500
#define UPPEST_BAND_FREQ 108000
#define CHANNEL_SPACE 100

static void quicktest_fm_init( CQuickTest* pMe);
static void quicktest_fm_power_up( void* pMe);
static void quicktest_fm_set_channel_to( CQuickTest* pMe, uint16 theNewChannel);
static void quicktest_fm_paint( CQuickTest* pMe);
#endif
#ifdef FEATURE_LED_CONTROL
static int disp_set_sigled_cmd(hs_sig_led_onoff_type onoff);
#endif //FEATURE_LED_CONTROL

/*==============================================================================
                                 全局数据
==============================================================================*/


/*==============================================================================
                                 本地（静态）数据
==============================================================================*/


/*==============================================================================
                                 函数定义
==============================================================================*/
/*==============================================================================
函数：QuickTest_UpdateActiveDialogInfo

说明：
       更新QuickTest Applet对象内关键的对话框参数。

参数：
       pMe [in]：指向QuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       wParam [in]：活动对话框资源ID；
       dwParam [in]:：指向活动对话框的IDialog接口指针。

返回值：
        无

备注：:
       更新后的QuickTest Apple对话框属性。QuickTest_RouteDialogEvent函数将
       根据这些属性把对话框事件路由至相应的处理函数。
       此函数仅由QuickTest_HandleEvent调用。

==============================================================================*/
void QuickTest_UpdateActiveDialogInfo
(
    CQuickTest *pMe,
    uint16  wParam,
    uint32 dwParam
)
{
    if (NULL == pMe)
    {
        return;
    }

    switch (wParam)
    {
        case IDD_MAINMENU:
        case IDD_KEYTEST:
        case IDD_YAMAHATEST:
        case IDD_VIBRATETEST:
        case IDD_BACKLIGHTTEST:         
        case IDD_FLIPTEST:
        case IDD_FMTEST:
        case IDD_SDTEST:
        case IDD_VERTEST:
        case IDD_LCDTEST:
#ifdef FEATURE_TOUCHPANEL
        case IDD_TOUCHSCREENTEST:
#endif
        case IDD_CALLTEST:
        case IDD_RESTORE_FACTORY:

            pMe->m_pActiveDlg = (IDialog*)dwParam;
            pMe->m_pActiveDlgID = wParam;
            return;

        default:
            return;
    }
}

/*==============================================================================
函数:
       QuickTest_ShowDialog
说明:
       函数由状态处理函数用来创建相应对话框资源ID的对话框。

参数:
       pMe [In]: 指向QuickTest Applet对象结构的指针,该结构包含小程序的特定信息.
       dlgResId [in]：对话框资源ID，函数根据该ID创建对话框。

返回值:
       无

备注:


==============================================================================*/
void QuickTest_ShowDialog(CQuickTest *pMe,uint16  dlgResId)
{
    int nRet;

    // At most one dialog open at once
    if (ISHELL_GetActiveDialog(pMe->m_pShell) != NULL)
    {
        // Looks like there is one dialog already opened.
        // Flag an error an return without doing anything.
        return;
    }

    nRet = ISHELL_CreateDialog(pMe->m_pShell,AEE_QUICKTEST_RES_FILE,dlgResId,NULL);
}

/*==============================================================================
函数:
       QuickTest_RouteDialogEvent
说明:
       函数将BREW事件路由给当前活动对话框的事件处理函数。

参数:
       pMe [In]: 指向QuickTest Applet对象结构的指针,该结构包含小程序的特定信息.
       eCode [in]：事件代码。
       wParam [in]：与事件eCode关联的数据。
       dwParam [in]：与事件eCode关联的数据。

返回值:
       TRUE：传入事件被处理。
       FALSE：传入事件没被处理。

备注:

==============================================================================*/
boolean QuickTest_RouteDialogEvent(CQuickTest *pMe,
    AEEEvent    eCode,
    uint16  wParam,
    uint32 dwParam
)
{
    if (NULL == pMe)
    {
        return FALSE;
    }
    if (NULL == pMe->m_pActiveDlg)
    {
        return FALSE;
    }
    switch (pMe->m_pActiveDlgID)
    {
        case IDD_MAINMENU:
            return QuickTest_MainMenuHandler(pMe,eCode,wParam,dwParam);

        case IDD_KEYTEST:
            return QuickTest_KeyTestHandler(pMe,eCode,wParam,dwParam);

        case IDD_YAMAHATEST:
            return QuickTest_YAMAHATestHandler(pMe,eCode,wParam,dwParam);

        case IDD_VIBRATETEST:
            return QuickTest_VibrateTestHandler(pMe,eCode,wParam,dwParam);

        case IDD_BACKLIGHTTEST:
            return QuickTest_BackLightTestHandler(pMe,eCode,wParam,dwParam);
            
        case IDD_FLIPTEST:
            return QuickTest_FlipTestHandler(pMe,eCode,wParam,dwParam);            

        case IDD_VERTEST:
            return QuickTest_VERTestHandler(pMe,eCode,wParam,dwParam);

#if defined( FEATURE_FM_RADIO)
        case IDD_FMTEST:
            return QuickTest_FMTestHandler(pMe,eCode,wParam,dwParam);
#endif

        case IDD_SDTEST:
            return QuickTest_SDTestHandler(pMe,eCode,wParam,dwParam);

        case IDD_LCDTEST:
            return QuickTest_LCDTestHandler(pMe,eCode,wParam,dwParam);

#ifdef FEATURE_TOUCHPANEL
        case IDD_TOUCHSCREENTEST:
            return QuickTest_TouchScreenTestHandler(pMe,eCode,wParam,dwParam);
#endif // FEATURE_TOUCHPANEL

        case IDD_CALLTEST:
            return QuickTest_CallHandler(pMe,eCode,wParam,dwParam);

        case IDD_RESTORE_FACTORY:
            return QuickTest_RestoreFactory_Handler(pMe,eCode,wParam,dwParam);

        default:
            return FALSE;
    }
}

/*==============================================================================
函数：
       QuickTest_MainMenuHandler
说明：
       IDD_MAINMENU对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_MainMenuHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    PARAM_NOT_REF(dwParam)

    IMenuCtl *pMenu = (IMenuCtl*)IDIALOG_GetControl(pMe->m_pActiveDlg,
                                                    IDC_MAINMENU);
    if (pMenu == NULL)
    {
        return FALSE;
    }

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
			//add by yangdecai
			{
				AECHAR WTitle[40] = {0};
				(void)ISHELL_LoadResString(pMe->m_pShell,
                        AEE_QUICKTEST_RES_FILE,                                
                        IDS_QUICKTEST,
                        WTitle,
                        sizeof(WTitle));
				IANNUNCIATOR_SetFieldText(pMe->m_pIAnn,WTitle);
            }
              IMENUCTL_AddItem(pMenu, AEE_QUICKTEST_RES_FILE, IDS_START, IDS_START, NULL, 0);
            (void)IMENUCTL_Redraw(pMenu);
            return TRUE;

        case EVT_DIALOG_START:
            IMENUCTL_SetProperties(pMenu, MP_UNDERLINE_TITLE|MP_WRAPSCROLL);

            IMENUCTL_SetSel(pMenu, pMe->m_mainMenuSel);

            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);
            return TRUE;

        case EVT_USER_REDRAW:
            (void)IMENUCTL_Redraw(pMenu);
            return TRUE;

        case EVT_DIALOG_END:
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    return TRUE;

                default:
                    break;
            }
            return TRUE;

        case EVT_COMMAND:
            pMe->m_mainMenuSel = IMENUCTL_GetSel(pMenu);
            switch (wParam)
            {
                case IDS_START:       //按键测试
                    CLOSE_DIALOG(DLGRET_VERTEST)
                    break;

                default:
                    ASSERT_NOT_REACHABLE;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_MainMenuHandler

/*==============================================================================
函数：
       QuickTest_KeyTestHandler
说明：
       IDD_KEYTEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_KeyTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    AECHAR   string[MAX_STRING_LENGTH+1];
    AEERect  dlgrc;

    PARAM_NOT_REF(dwParam)

    MEMSET(string, 0, sizeof(string));
    SETAEERECT(&dlgrc,
               0,
               0,
               pMe->m_rc.dx,
               pMe->m_rc.dy);

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            return TRUE;

        case EVT_DIALOG_START:
            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);
            return TRUE;

        case EVT_USER_REDRAW:
			{

					IImage* image	= NULL;
					image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_KEY_TEST);
				
					if( image != NULL)
					{
						DBGPRINTF("IImage IS NOT NULL........................");
						IIMAGE_Draw(image, 0, 0);
						IIMAGE_Release( image);
					}
					DBGPRINTF("IImage IS NULL........................");
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);

				
            }
            return TRUE;

        case EVT_DIALOG_END:
            return TRUE;
		case EVT_KEY_PRESS:
		case EVT_KEY_RELEASE:
			{
				switch(wParam)
            	{
            		case AVK_ENDCALL:
					//case AVK_END:
					{
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					 
						if( image != NULL)
						{
							IIMAGE_Draw(image, 136, 0);
							IIMAGE_Draw(image, 140, 0);
							IIMAGE_Draw(image, 136, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 140, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 136, 50-TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 140, 50-TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 136, TITLEBAR_HEIGHT*2);
							IIMAGE_Draw(image, 140, TITLEBAR_HEIGHT*2);
							IIMAGE_Release( image);
						}
						IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
						return TRUE;
            		}
					default:
						break;
				}
			}
			break;
        case EVT_KEY:
			
            switch(wParam)
            {
            	case AVK_ENDCALL:
				//case AVK_END:
					{
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					    
						if( image != NULL)
						{
							IIMAGE_Draw(image, 136, 0);
							IIMAGE_Draw(image, 140, 0);
							IIMAGE_Draw(image, 136, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 140, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 136, 50-TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 140, 50-TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 136, TITLEBAR_HEIGHT*2);
							IIMAGE_Draw(image, 140, TITLEBAR_HEIGHT*2);
							IIMAGE_Release( image);
						}
						IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
						return TRUE;
					}
					break;
                case AVK_CLR:
					{
						IImage* image	= NULL;
						
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
						if((uint32)dwParam == 1)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*9, 66);
						}
						else
						{
							IIMAGE_Draw(image, 116, 0);
							IIMAGE_Draw(image, 120, 0);
							IIMAGE_Draw(image, 116, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 120, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 116, 50-TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 120, 50-TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 116, TITLEBAR_HEIGHT*2);
							IIMAGE_Draw(image, 120, TITLEBAR_HEIGHT*2);
							
						}
						if(pMe->m_testkeycount >=45)
						{
	                     	CLOSE_DIALOG(DLGRET_CANCELED)
						}
						IIMAGE_Release( image);
						IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                	}
                     break;

                case AVK_0:
					{
	                    IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*2, 98);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
						IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                	}
                    break;

                case AVK_1:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT, 50);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_2:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*2, 50);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_3:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*3, 50);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_4:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT, 66);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_5:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*2, 66);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_6:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*3, 66);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_7:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT, 82);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_8:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*2, 82);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_9:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*3, 82);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_STAR:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, 0, 66);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_POUND:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, 0, 50);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_SELECT:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, 22, 0);
							IIMAGE_Draw(image, 26, 0);
							IIMAGE_Draw(image, 22, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 26, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 22, 50-TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 26, 50-TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 22, TITLEBAR_HEIGHT*2);
							IIMAGE_Draw(image, 26, TITLEBAR_HEIGHT*2);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_SEND:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, 0, 0);
							IIMAGE_Draw(image, 4, 0);
							IIMAGE_Draw(image, 0, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 4, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 0, 50-TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 4, 50-TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 0, TITLEBAR_HEIGHT*2);
							IIMAGE_Draw(image, 4, TITLEBAR_HEIGHT*2);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
               case AVK_INFO:
					{
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, 66, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 82, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 66, TITLEBAR_HEIGHT+2);
							IIMAGE_Draw(image, 82, TITLEBAR_HEIGHT+2);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_UP:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					    DBGPRINTF("AVK_UPwParam::::::::::::::::::::%d,dwParam:::::::::::::::::%d",wParam,dwParam);
						if( image != NULL)
						{
							if((uint32)dwParam == 1)
							{
								IIMAGE_Draw(image, TITLEBAR_HEIGHT*3, 98);
								pMe->m_testkeycount ++;
							}
							else
							{
								IIMAGE_Draw(image, 66, 0);
								IIMAGE_Draw(image, 82, 0);
								pMe->m_testkeycount ++;
							}
							
						}
						IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
						IIMAGE_Release( image);
                     }
					break;
                case AVK_DOWN:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					    DBGPRINTF("AVK_DOWNwParam::::::::::::::::::::%d,dwParam:::::::::::::::::%d",wParam,dwParam);
						if( image != NULL)
						{
							if((uint32)dwParam == 1)
							{
								IIMAGE_Draw(image, TITLEBAR_HEIGHT*6, 98);
								pMe->m_testkeycount ++;
							}
							else
							{
								IIMAGE_Draw(image, 66, 34);
								IIMAGE_Draw(image, 82, 34);
								pMe->m_testkeycount ++;
							}
							IIMAGE_Release( image);
						}
                     }
					 IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                     break;

                case AVK_LEFT:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, 44, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 44, TITLEBAR_HEIGHT+2);
							IIMAGE_Draw(image, 66-TITLEBAR_HEIGHT, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 66-TITLEBAR_HEIGHT, TITLEBAR_HEIGHT+2);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;

                case AVK_RIGHT:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, 94, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 94, TITLEBAR_HEIGHT+2);
							IIMAGE_Draw(image, 116-TITLEBAR_HEIGHT, TITLEBAR_HEIGHT);
							IIMAGE_Draw(image, 116-TITLEBAR_HEIGHT, TITLEBAR_HEIGHT+2);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				
				case AVK_T:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*4, 50);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
                    
                     break;
			    case AVK_Y:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*5, 50);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
			     case AVK_U:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*6, 50);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				 case AVK_I:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*7, 50);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
			      case AVK_O:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*8, 50);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
			      case AVK_P:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*9, 50);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				 case AVK_G:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*4, 66);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				 case AVK_H:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*5, 66);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				case AVK_J:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*6, 66);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
			     case AVK_K:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*7, 66);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				 case AVK_L:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*8, 66);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
			     
			      case AVK_V:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*4, 82);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				 case AVK_B:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*5, 82);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				 case AVK_N:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*6, 82);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				case AVK_M:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*7, 82);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
			     case AVK_RWD:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*8, 82);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				 case AVK_ENTER:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*9, 82);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
			      case AVK_SHIFT:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, 0, 82);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
			      case AVK_SPACE:
                     {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*4, 98);
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*5, 98);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                     }
					 IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                     break;
				 case AVK_SYMBOL:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*7, 98);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                     }
					 IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                     break;
				 case AVK_CAPLK:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, 0, 98);
							IIMAGE_Draw(image, TITLEBAR_HEIGHT, 98);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                    }
					IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                    break;
				 case AVK_LCTRL:
                    {
						IImage* image	= NULL;
						image = ISHELL_LoadResImage( pMe->m_pShell, AEE_APPSCOMMONRES_IMAGESFILE, IDI_TEST_DOWN);
					
						if( image != NULL)
						{
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*8, 98);
							IIMAGE_Draw(image, TITLEBAR_HEIGHT*9, 98);
							IIMAGE_Release( image);
						}
						pMe->m_testkeycount ++;
                     }
					 IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                     break;
					 
                default:
                    break;
            }
			
			
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_KeyTestHandler

/*==============================================================================
函数：
       QuickTest_YAMAHATestHandler
说明：
       IDD_YAMAHATEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_YAMAHATestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    AECHAR   string[MAX_STRING_LENGTH+1];
    AEERect  dlgrc;

    PARAM_NOT_REF(dwParam)

    MEMSET(string, 0, sizeof(string));
    SETAEERECT(&dlgrc,
               0,
               0,
               pMe->m_rc.dx,
               pMe->m_rc.dy);

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            return TRUE;

        case EVT_DIALOG_START:
            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);
            return TRUE;

        case EVT_USER_REDRAW:
            //绘制测试提示语
            (void)ISHELL_LoadResString(pMe->m_pShell,
                                       AEE_QUICKTEST_RES_FILE,
                                       IDS_YAMAHAINTEST,
                                       string,
                                       MAX_STRING_LENGTH);
            if(string[0] == 0)
            {
                return TRUE;
            }
            (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                    AEE_FONT_BOLD,
                                    string,
                                    -1,
                                    0,
                                    0,
                                    &dlgrc,
                                    IDF_ALIGN_CENTER|IDF_ALIGN_MIDDLE);

            // 统一更新界面
            IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
            IALERT_StartRingerPreview(pMe->m_pIAlert, 0);
            QuickTest_Ringer(pMe);
            return TRUE;

        case EVT_DIALOG_END:
           (void)IRINGERMGR_Stop(pMe->m_pRingerMgr);
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
                    (void)IRINGERMGR_Stop(pMe->m_pRingerMgr);
                    (void)ISHELL_CancelTimer(pMe->m_pShell,
                                 (PFNNOTIFY)(QuickTest_Ringer),
                                  pMe);
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    break;

                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_YAMAHATestHandler

/*==============================================================================
函数：
       QuickTest_VibrateTestHandler
说明：
       IDD_VIBRATETEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_VibrateTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    AECHAR   string[MAX_STRING_LENGTH+1];
    AEERect  dlgrc;

    PARAM_NOT_REF(dwParam)

    MEMSET(string, 0, sizeof(string));
    SETAEERECT(&dlgrc,
               0,
               0,
               pMe->m_rc.dx,
               pMe->m_rc.dy);

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            return TRUE;

        case EVT_DIALOG_START:
            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);
            return TRUE;

        case EVT_USER_REDRAW:
            //绘制测试提示语
            (void)ISHELL_LoadResString(pMe->m_pShell,
                                       AEE_QUICKTEST_RES_FILE,
                                       IDS_VIBRATEINTEST,
                                       string,
                                       MAX_STRING_LENGTH);
            if(string[0] == 0)
            {
                return TRUE;
            }
            (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                    AEE_FONT_BOLD,
                                    string,
                                    -1,
                                    0,
                                    0,
                                    &dlgrc,
                                    IDF_ALIGN_CENTER|IDF_ALIGN_MIDDLE);

            // 统一更新界面
            IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
            QuickTest_Vibrate(pMe);
            return TRUE;

        case EVT_DIALOG_END:
            (void)ISOUND_StopVibrate(pMe->m_pISound);
            (void)ISHELL_CancelTimer(pMe->m_pShell,
                                    (PFNNOTIFY)(QuickTest_Vibrate),
                                     pMe);
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
                    (void)ISOUND_StopVibrate(pMe->m_pISound);
                    (void)ISHELL_CancelTimer(pMe->m_pShell,
                                 (PFNNOTIFY)(QuickTest_Vibrate),
                                  pMe);
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    break;

                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_VibrateTestHandler

/*==============================================================================
函数：
       QuickTest_BackLightTestHandler
说明：
       IDD_BACKLIGHTTEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_BackLightTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    AECHAR   string[MAX_STRING_LENGTH+1];
    AEERect  dlgrc;
    byte     nTmplevel;
    
    PARAM_NOT_REF(dwParam)

    SETAEERECT(&dlgrc,
               0,
               0,
               pMe->m_rc.dx,
               pMe->m_rc.dy);

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            return TRUE;

        case EVT_DIALOG_START:
            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);
            return TRUE;

        case EVT_USER_REDRAW:
            MEMSET(string, 0, sizeof(string));            
            //绘制标题
            (void)ISHELL_LoadResString(pMe->m_pShell,
                                       AEE_QUICKTEST_RES_FILE,
                                       IDS_BACKLIGHTTEST,
                                       string,
                                       MAX_STRING_LENGTH);
            if(string[0] == 0)
            {
                return TRUE;
            }            
            (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                    AEE_FONT_BOLD,
                                    string,
                                    -1,
                                    0,
                                    0,
                                    NULL,
                                    IDF_TEXT_TRANSPARENT);
            
            //绘制第一句提示语
            MEMSET(string, 0, sizeof(string));              
            (void)ISHELL_LoadResString(pMe->m_pShell,
                                       AEE_QUICKTEST_RES_FILE,
                                       IDS_BACKLIGHTON,
                                       string,
                                       MAX_STRING_LENGTH);
            if(string[0] == 0)
            {
                return TRUE;
            }
            (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                    AEE_FONT_BOLD,
                                    string,
                                    -1,
                                    0,
                                    pMe->m_lineheight*1,
                                    NULL,
                                    IDF_TEXT_TRANSPARENT);

            //绘制第二句提示语
            MEMSET(string, 0, sizeof(string));
            (void)ISHELL_LoadResString(pMe->m_pShell,
                                       AEE_QUICKTEST_RES_FILE,
                                       IDS_BACKLIGHTOFF,
                                       string,
                                       MAX_STRING_LENGTH);
            if(string[0] == 0)
            {
                return TRUE;
            }
            (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                    AEE_FONT_BOLD,
                                    string,
                                    -1,
                                    0,
                                    pMe->m_lineheight*2,
                                    NULL,
                                    IDF_TEXT_TRANSPARENT);
#ifdef FEATURE_LED_CONTROL
            //绘制第三句提示语
            MEMSET(string, 0, sizeof(string));
            (void)ISHELL_LoadResString(pMe->m_pShell,
                                       AEE_QUICKTEST_RES_FILE,
                                       IDS_LEDON,
                                       string,
                                       MAX_STRING_LENGTH);
            if(string[0] == 0)
            {
                return TRUE;
            }
            (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                    AEE_FONT_BOLD,
                                    string,
                                    -1,
                                    0,
                                    pMe->m_lineheight*3,
                                    NULL,
                                    IDF_TEXT_TRANSPARENT);

            //绘制第四句提示语
            MEMSET(string, 0, sizeof(string));
            (void)ISHELL_LoadResString(pMe->m_pShell,
                                       AEE_QUICKTEST_RES_FILE,
                                       IDS_LEDOFF,
                                       string,
                                       MAX_STRING_LENGTH);
            if(string[0] == 0)
            {
                return TRUE;
            }
            (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                    AEE_FONT_BOLD,
                                    string,
                                    -1,
                                    0,
                                    pMe->m_lineheight*4,
                                    NULL,
                                    IDF_TEXT_TRANSPARENT);
#endif //FEATURE_LED_CONTROL

            // 统一更新界面
            IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
            return TRUE;

        case EVT_DIALOG_END:
            (void) ICONFIG_SetItem(pMe->m_pConfig,
                                   CFGI_BACKLIGHT_LEVEL,
                                   &pMe->m_nlightlevel,
                                   sizeof(pMe->m_nlightlevel));
            IBACKLIGHT_TurnOn(pMe->m_pIBacklight);
#ifdef FEATURE_LED_CONTROL            
            disp_set_sigled_cmd(HS_SIG_LED_COLOR_NONE);
#endif //FEATURE_LED_CONTROL
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
                    (void) ICONFIG_SetItem(pMe->m_pConfig,
                                           CFGI_BACKLIGHT_LEVEL,
                                           &pMe->m_nlightlevel,
                                           sizeof(pMe->m_nlightlevel));
                    IBACKLIGHT_TurnOn(pMe->m_pIBacklight);
                    CLOSE_DIALOG(DLGRET_CANCELED);
                    break;	

		   default:
                   break;
	  }
         return TRUE;

        case EVT_KEY_RELEASE:
            switch(wParam)
            {
                case AVK_1:
                    nTmplevel = 7;
                    (void) ICONFIG_SetItem(pMe->m_pConfig,
                                           CFGI_BACKLIGHT_LEVEL,
                                           &nTmplevel,
                                           sizeof(nTmplevel));
                    IBACKLIGHT_TurnOn(pMe->m_pIBacklight);
                    break;

                case AVK_2:
#ifndef WIN32
                    oemui_is_lcd_test_state(1);
#endif
                    IBACKLIGHT_TurnOff(pMe->m_pIBacklight);
                    break;

#ifdef FEATURE_LED_CONTROL
                case AVK_3:                    
                    disp_set_sigled_cmd(HS_SIG_LED_COLOR_ORANGE_ON);
                    disp_set_sigled_cmd(HS_SIG_LED_COLOR_WHITE_ON);
                    disp_set_sigled_cmd(HS_SIG_LED_COLOR_RED_ON);                   
                    break;

                case AVK_4:
                    disp_set_sigled_cmd(HS_SIG_LED_COLOR_NONE);
                    break;
#endif //FEATURE_LED_CONTROL                     

                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_BackLightTestHandler

/*==============================================================================
函数：
       QuickTest_FlipTestHandler
说明：
       IDD_FLIPTEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_FlipTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    AECHAR string[MAX_STRING_LENGTH+1];
    static boolean  flippass = FALSE;
    uint16 ResId;
    
    PARAM_NOT_REF(dwParam)

    MEMSET(string, 0, sizeof(string));

    switch (eCode)
    {
        case EVT_DIALOG_INIT:         
            return TRUE;

        case EVT_DIALOG_START:
            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);
            return TRUE;

        case EVT_USER_REDRAW:
            if(flippass == TRUE)
            {
                ResId = IDS_FLIPTEST_PASS; 
                flippass = FALSE;
            }
            else
            {
                ResId = IDS_FLIPTEST; 
            }   
            IDISPLAY_EraseRect(pMe->m_pDisplay, &pMe->m_rc);
            //绘制标题
            MEMSET(string, 0, sizeof(string));               
            (void)ISHELL_LoadResString(pMe->m_pShell,
                                       AEE_QUICKTEST_RES_FILE,
                                       IDS_FLIPTEST_TITLE,
                                       string,
                                       MAX_STRING_LENGTH);
            if(string[0] == 0)
            {
                return TRUE;
            }            
            (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                    AEE_FONT_BOLD,
                                    string,
                                    -1,
                                    0,
                                    0,
                                    NULL,
                                    IDF_TEXT_TRANSPARENT);  

          
            //绘制结果
             MEMSET(string, 0, sizeof(string));             
            (void)ISHELL_LoadResString(pMe->m_pShell,
                                       AEE_QUICKTEST_RES_FILE,
                                       ResId,
                                       string,
                                       MAX_STRING_LENGTH);
            if(string[0] == 0)
            {
                return TRUE;
            }            
            (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                    AEE_FONT_BOLD,
                                    string,
                                    -1,
                                    0,
                                    pMe->m_lineheight*2,
                                    NULL,
                                    IDF_TEXT_TRANSPARENT);              

            // 统一更新界面
            IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
            return TRUE;

        case EVT_DIALOG_END:
            return TRUE;

        case EVT_FLIP:// wParam = TRUE if open, FALSE if closed.
            flippass = TRUE;
            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);            
            return TRUE;  

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    break;       

                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_FlipTestHandler

/*==============================================================================
函数：
       QuickTest_FMTestHandler
说明：
       IDD_FMTEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
#if defined( FEATURE_FM_RADIO)
#ifdef WIN32
static uint16 channel = 0;
#endif
static boolean  QuickTest_FMTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    AECHAR   string[MAX_STRING_LENGTH+1];
    AEERect  dlgrc;

    PARAM_NOT_REF(dwParam)

    MEMSET(string, 0, sizeof(string));
    SETAEERECT(&dlgrc,
               0,
               0,
               pMe->m_rc.dx,
               pMe->m_rc.dy);

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            quicktest_fm_init( pMe);
            return TRUE;

        case EVT_DIALOG_START:
            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);
            return TRUE;

        case EVT_USER_REDRAW:
            quicktest_fm_paint( pMe);
            return TRUE;

        case EVT_DIALOG_END:
#ifndef WIN32
            if( pMe->m_fmIsPowerupBeforeFmTest)
            {
                fm_tune_channel( pMe->m_fmChannelBeforeFmTest);
            }
            else
            {
            	if (HS_HEADSET_ON())
            	{
            		fm_mute(TRUE);
            	}	            
                fm_radio_power_down();
            }
#endif
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    break;

                case AVK_UP:
                case AVK_DOWN:
                {
#ifndef WIN32 
                    uint16 channel = fm_radio_get_playing_channel() + ( wParam == AVK_UP ? 1 : -1);
#else
                    channel = channel + ( wParam == AVK_UP ? 1 : -1);
#endif
					if( channel * CHANNEL_SPACE > UPPEST_BAND_FREQ)
			        {
			            channel = 0;
			        }
			        else if( channel < 0)
			        {
			            channel = ( UPPEST_BAND_FREQ - LOWEST_BAND_FREQ) / CHANNEL_SPACE;
			        }
			        
                    quicktest_fm_set_channel_to( pMe, channel);
                }
                break;

                case AVK_LEFT:
                case AVK_RIGHT:
                {
#ifndef WIN32 
                    uint16 channel = fm_radio_get_playing_channel() + ( wParam == AVK_RIGHT ? 1 : -1);
#else
                    channel = channel + ( wParam == AVK_RIGHT ? 1 : -1);
#endif
					if( channel * CHANNEL_SPACE > UPPEST_BAND_FREQ )
			        {
			            channel = 0;
			        }
			        else if( channel < 0)
			        {
			            channel = ( UPPEST_BAND_FREQ - LOWEST_BAND_FREQ) / CHANNEL_SPACE;
			        }
			        
                    quicktest_fm_set_channel_to( pMe, channel);
				}
				break;

                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_FMTestHandler
#endif

/*==============================================================================
函数：
       QuickTest_SDTestHandler
说明：
       IDD_SDTEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_SDTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    AECHAR   string[MAX_STRING_LENGTH+1];
    AEERect  dlgrc;
    int  uim;

    PARAM_NOT_REF(dwParam)

    MEMSET(string, 0, sizeof(string));
    SETAEERECT(&dlgrc,
               0,
               0,
               pMe->m_rc.dx,
               pMe->m_rc.dy);
    if (IsRunAsUIMVersion())
    {
        if(IRUIM_IsCardConnected(pMe->m_pIRUIM))
        {
            uim = 1;
        }
        else
        {
            uim = 3;
        }
    }
    else
    {
        uim = 2;
    }

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            return TRUE;

        case EVT_DIALOG_START:
            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);
            return TRUE;

        case EVT_USER_REDRAW:
        {
            if(uim < 2)
            {
                //绘制测试提示语
                (void)ISHELL_LoadResString(pMe->m_pShell,
                                           AEE_QUICKTEST_RES_FILE,
                                           IDS_UIM,
                                           string,
                                           MAX_STRING_LENGTH);
                if(string[0] == 0)
                {
                    return TRUE;
                }
                (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                        AEE_FONT_BOLD,
                                        string,
                                        -1,
                                        0,
                                        dlgrc.dy/2-16,
                                        &dlgrc,
                                        IDF_ALIGN_CENTER);

                // 统一更新界面
                IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
            }
            else if(uim > 2)
            {
                (void)ISHELL_LoadResString(pMe->m_pShell,
                                           AEE_QUICKTEST_RES_FILE,
                                           IDS_NOUIM,
                                           string,
                                           MAX_STRING_LENGTH);
                if(string[0] == 0)
                {
                    return TRUE;
                }
                (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                        AEE_FONT_BOLD,
                                        string,
                                        -1,
                                        0,
                                        dlgrc.dy/2-16,
                                        &dlgrc,
                                        IDF_ALIGN_CENTER);

                // 统一更新界面
                IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
            }
            else
            {
                //绘制测试提示语
                (void)ISHELL_LoadResString(pMe->m_pShell,
                                           AEE_QUICKTEST_RES_FILE,
                                           IDS_NOCARD_VER,
                                           string,
                                           MAX_STRING_LENGTH);
                if(string[0] == 0)
                {
                    return TRUE;
                }
                (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                        AEE_FONT_BOLD,
                                        string,
                                        -1,
                                        0,
                                        dlgrc.dy/2-16,
                                        &dlgrc,
                                        IDF_ALIGN_CENTER);

                // 统一更新界面
                IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
            }
        }
            return TRUE;

        case EVT_DIALOG_END:
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    break;

                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_SDTestHandler

/*==============================================================================
函数：
       QuickTest_VERTestHandler
说明：
       IDD_VERTEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_VERTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    PARAM_NOT_REF(dwParam)

    IStatic *pStatic = (IStatic*)IDIALOG_GetControl(pMe->m_pActiveDlg,
                                                    IDC_VER_STAT);
    if (pStatic == NULL)
    {
        return FALSE;
    }

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            return TRUE;

        case EVT_DIALOG_START:
            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);
            return TRUE;

        case EVT_USER_REDRAW:
         {
                        AECHAR szBuf[320];
                        IDialog *p_dlg;
                        IStatic *p_stk;
                        int n = 0;
                        uint32 esn;
                        AECHAR fmt_str[20];

                        (void)MEMSET( szBuf,(AECHAR) 0, sizeof(szBuf));

                        (void) ISHELL_LoadResString(pMe->m_pShell,
                                                   AEE_QUICKTEST_RES_FILE,
                                                   IDS_SW_VERSION,
                                                   szBuf,
                                                   sizeof(szBuf));

                        n = WSTRLEN(szBuf);
                        szBuf[n++] = (AECHAR) '\n';

                        (void) ICONFIG_GetItem(pMe->m_pConfig,
                                              CFGI_BUILD_VERSION,
                                              (szBuf + n),
                                              sizeof(szBuf));

                        n = WSTRLEN(szBuf);
                        szBuf[n++] = (AECHAR) '\n';

                        {
                            (void) ISHELL_LoadResString(pMe->m_pShell,
                                                       AEE_QUICKTEST_RES_FILE,
                                                       IDS_ESN,
                                                       (szBuf + n),
                                                       sizeof(szBuf));

                            n = WSTRLEN(szBuf);
                            szBuf[n++] = (AECHAR) '\n';

                            (void) ICONFIG_GetItem(pMe->m_pConfig,
                                                  CFGI_ESN,
                                                  &esn,
                                                  sizeof(esn));

                            STRTOWSTR("%u %u", fmt_str, sizeof(fmt_str));

                            WSPRINTF((szBuf + n),
                                    sizeof(szBuf),
                                    fmt_str,
                                    ((esn & 0xFF000000) >> 24),
                                    (esn & 0x00FFFFFF));

                            n = WSTRLEN(szBuf);
                            szBuf[n++] = (AECHAR) '\n';

                            //Display ESN with hexadecimal
                            STRTOWSTR("0x%08X", fmt_str, sizeof(fmt_str));
                            WSPRINTF((szBuf + n),
                                    sizeof(szBuf),
                                    fmt_str,
                                    esn);

                            n = WSTRLEN(szBuf);
                            szBuf[n++] = (AECHAR) '\n';
                        }
                        p_dlg = ISHELL_GetActiveDialog(pMe->m_pShell);
                        p_stk = (IStatic *) IDIALOG_GetControl(p_dlg, IDC_VER_STAT);

                        // Set the values of the title and text strings for this control
                        (void) ISTATIC_SetText(p_stk,
                                               NULL,
                                               szBuf,
                                               AEE_FONT_BOLD,
                                               AEE_FONT_BOLD);

                        (void) ISTATIC_Redraw(p_stk);
              }
              return TRUE;

        case EVT_DIALOG_END:
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    break;

                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_VERTestHandler
/*==============================================================================
函数：
       QuickTest_LCDTestHandler
说明：
       IDD_LCDTEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_LCDTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    PARAM_NOT_REF(dwParam)

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            return TRUE;

        case EVT_DIALOG_START:
            (void) ISHELL_PostEvent( pMe->m_pShell,
                                     AEECLSID_QUICKTEST,
                                     EVT_USER_REDRAW,
                                     0,
                                     0);
            return TRUE;

        case EVT_USER_REDRAW:
            //绘制各种颜色的界面
#ifdef FEATURE_SUPPORT_BT_APP
            if(pMe->m_dilag_type == BT_TEST)
            {
                //AECHAR   string[MAX_STRING_LENGTH+1];
                //ISHELL_LoadResString(pMe->m_pShell,
                //                       AEE_QUICKTEST_RES_FILE,
                //                       IDS_BLUETOOTH_TEST,
                //                       string,
                //                       MAX_STRING_LENGTH);
                IDISPLAY_DrawText(pMe->m_pDisplay,
                                        AEE_FONT_BOLD,
                                        L"Bluetooth test",
                                        -1,
                                        0,
                                        0,
                                        &pMe->m_rc,
                                        IDF_ALIGN_CENTER|IDF_ALIGN_MIDDLE);
                IDISPLAY_Update( pMe->m_pDisplay);
            }
            else
#endif
            {
                pMe->colorMask = 0;
                quicktest_ChangeColor(pMe);
            }
            return TRUE;

        case EVT_DIALOG_END:
#ifdef FEATURE_SUPPORT_BT_APP
            if(pMe->m_dilag_type ==LCD_TEST)
            {
                pMe->colorMask = 0;
            }
#endif
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
#ifdef FEATURE_SUPPORT_BT_APP
                    if(pMe->m_dilag_type == BT_TEST)
                    {
                    }
                    else
#endif
                    {
                        (void)ISHELL_CancelTimer(pMe->m_pShell,
                                     (PFNNOTIFY)(quicktest_ChangeColor),
                                      pMe);
                    }
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    break;
#ifdef FEATURE_SUPPORT_BT_APP
                case AVK_SELECT:
                    if(pMe->m_dilag_type == BT_TEST)
                    {
                        ISHELL_StartAppletArgs(pMe->m_pShell, AEECLSID_BTUIAPP, "Q");
                    }
                    break;
#endif
                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_LCDTestHandler

#ifdef FEATURE_TOUCHPANEL
/*==============================================================================
函数：
       QuickTest_TouchScreenTestHandler
说明：
       IDD_TOUCHSCREENTEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_TouchScreenTestHandler(CQuickTest *pMe,
    AEEEvent eCode,
    uint16 wParam,
    uint32 dwParam
)
{
    AEERect  dlgrc;

    PARAM_NOT_REF(dwParam)

    SETAEERECT(&dlgrc,
               0,
               0,
               pMe->m_rc.dx,
               pMe->m_rc.dy);

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            return TRUE;

        case EVT_DIALOG_START:
            (void)ISHELL_PostEvent( pMe->m_pShell,
                                    AEECLSID_QUICKTEST,
                                    EVT_USER_REDRAW,
                                    0,
                                    0);
            return TRUE;

        case EVT_USER_REDRAW:
            {
#ifndef WIN32
                AECHAR   string[4][MAX_STRING_LENGTH+1];
                MEMSET(string, 0, sizeof(string));
                //装载字符串
                (void)ISHELL_LoadResString(pMe->m_pShell,
                                           AEE_QUICKTEST_RES_FILE,
                                           IDS_DRAWOPTIONALLY,
                                           string[0],
                                           MAX_STRING_LENGTH);
                (void)ISHELL_LoadResString(pMe->m_pShell,
                                           AEE_QUICKTEST_RES_FILE,
                                           IDS_OKTOCALIBRATE,
                                           string[1],
                                           MAX_STRING_LENGTH);
                (void)ISHELL_LoadResString(pMe->m_pShell,
                                           AEE_QUICKTEST_RES_FILE,
                                           IDS_UPTOCLEARSCREEN,
                                           string[2],
                                           MAX_STRING_LENGTH);
                (void)ISHELL_LoadResString(pMe->m_pShell,
                                           AEE_QUICKTEST_RES_FILE,
                                           IDS_DOWNTOLINEARITY,
                                           string[3],
                                           MAX_STRING_LENGTH);

                //绘制测试提示语
                (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                        AEE_FONT_BOLD,
                                        string[0],
                                        -1,
                                        0,
                                        dlgrc.dy/2-32,
                                        &dlgrc,
                                        IDF_ALIGN_CENTER);

                //绘制第二句提示语
                (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                        AEE_FONT_BOLD,
                                        string[1],
                                        -1,
                                        0,
                                        dlgrc.dy/2-16,
                                        &dlgrc,
                                        IDF_ALIGN_CENTER);

                //绘制第三句提示语
                (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                        AEE_FONT_BOLD,
                                        string[2],
                                        -1,
                                        0,
                                        dlgrc.dy/2,
                                        &dlgrc,
                                        IDF_ALIGN_CENTER);

                //绘制第四句提示语
                (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                        AEE_FONT_BOLD,
                                        string[3],
                                        -1,
                                        0,
                                        dlgrc.dy/2+16,
                                        &dlgrc,
                                        IDF_ALIGN_CENTER);

                // 统一更新界面
                IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
#endif
            }
            return TRUE;

        case EVT_DIALOG_END:
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    break;

#ifdef FEATURE_APP_CALIAPP
                case AVK_SELECT:
                    {
                        int ret;
                        ret = ISHELL_StartApplet( pMe->m_pShell,
                                                  AEECLSID_APP_CALIAPP);
                        if ( (SUCCESS != ret) && (EALREADY != ret) )
                        {
                            return TRUE;
                        }
                    }
                    break;
#endif //!FEATURE_APP_CALIAPP

                case AVK_UP:
                    IDISPLAY_FillRect(pMe->m_pDisplay,
                                      &dlgrc,
                                      CLR_SYS_WIN);
                    (void)ISHELL_PostEvent( pMe->m_pShell,
                                            AEECLSID_QUICKTEST,
                                            EVT_USER_REDRAW,
                                            0,
                                            0);
                    break;

                case AVK_DOWN:
                    break;

                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_TouchScreenTestHandler
#endif // FEATURE_TOUCHPANEL

/*==============================================================================
函数：
       QuickTest_CallHandler
说明：
       IDD_CALLTEST对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_CallHandler(CQuickTest *pMe,
                                      AEEEvent eCode,
                                      uint16 wParam,
                                      uint32 dwParam
)
{

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            return TRUE;

        case EVT_DIALOG_START:
#ifndef WIN32
            pMe->m_qdspisr = qdsp_cmd_isr_table[QDSP_ISR_INT0];
#endif
            quicktest_mic_receiver_Loopback(pMe);
            (void)ISHELL_PostEvent( pMe->m_pShell,
                                    AEECLSID_QUICKTEST,
                                    EVT_USER_REDRAW,
                                    0,
                                    0);
            return TRUE;

        case EVT_USER_REDRAW:
        {
            AECHAR   string[MAX_STRING_LENGTH+1];
            IDISPLAY_ClearScreen(pMe->m_pDisplay);
#ifndef WIN32
            if(HS_HEADSET_ON())
            {
                STRTOWSTR("headset loop",string,sizeof(string));
            }
            else
#endif
            {
                STRTOWSTR("HANDSET LOOP",string,sizeof(string));
            }
            (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                    AEE_FONT_BOLD,
                                    string,
                                    -1,
                                    0,
                                    0,
                                    NULL,
                                    IDF_ALIGN_CENTER);
            IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
         }
            return TRUE;

        case EVT_DIALOG_END:
#ifndef WIN32
            voc_release(VOC_ACQ_TEST);
            qdsp_cmd_set_isr(pMe->m_qdspisr);
#endif
            return TRUE;

       case EVT_HEADSET:
            quicktest_mic_receiver_Loopback(pMe);
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {

                case AVK_CLR:
#ifndef WIN32
                    voc_release(VOC_ACQ_TEST);
                    qdsp_cmd_set_isr(pMe->m_qdspisr);
#endif
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    break;

                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_CallHandler

/*==============================================================================
函数：
       QuickTest_RestoreFactory_Handler
说明：
       IDD_RESTORE_FACTORY对话框事件处理函数

参数：
       pMe [in]：指向CQuickTest Applet对象结构的指针。该结构包含小程序的特定信息。
       eCode [in]：事件代码。
       wParam：事件相关数据。
       dwParam：事件相关数据。

返回值：
       TRUE：传入事件被处理。
       FALSE：传入事件被忽略。

备注：

==============================================================================*/
static boolean  QuickTest_RestoreFactory_Handler(CQuickTest *pMe,
                                      AEEEvent eCode,
                                      uint16 wParam,
                                      uint32 dwParam
)
{
    //ICallList      *m_pCallList = NULL;uint32 value;byte alertType;  
    ICallHistory *pCallHistory = NULL;
    uint32        value;
    byte alertType;  

    switch (eCode)
    {
        case EVT_DIALOG_INIT:
            return TRUE;

        case EVT_DIALOG_START:
            (void)ISHELL_PostEvent( pMe->m_pShell,
                                    AEECLSID_QUICKTEST,
                                    EVT_USER_REDRAW,
                                    0,
                                    0);
            return TRUE;

        case EVT_USER_REDRAW:
            {
                AECHAR   string[MAX_STRING_LENGTH+1];
                (void)ISHELL_LoadResString(pMe->m_pShell,
                                           AEE_QUICKTEST_RES_FILE,
                                           IDS_RESTORE_FACTORY,
                                           string,
                                           MAX_STRING_LENGTH);


                (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                                        AEE_FONT_BOLD,
                                        string,
                                        -1,
                                        0,
                                        0,
                                        NULL,
                                        IDF_ALIGN_CENTER);


                IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
                OEM_RestoreFactorySetting();                                    
                value = 0;
                if (AEE_SUCCESS == ISHELL_CreateInstance(pMe->m_pShell, AEECLSID_CALLHISTORY, (void **)&pCallHistory))
                //if (AEE_SUCCESS == ISHELL_CreateInstance(pMe->m_pShell, AEECLSID_CALLLIST, (void **)&m_pCallList))
                {
                  //ICALLLIST_Reset(m_pCallList);
                  ICALLHISTORY_Clear(pCallHistory);
                  IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_CALL,ANNUN_STATE_CALL_MISSEDCALL_OFF);
                  {
                      boolean missed_call_icon;
                      missed_call_icon = FALSE;
                      (void) ICONFIG_SetItem(pMe->m_pConfig,
                                         CFGI_MISSED_CALL_ICON,
                                         &missed_call_icon,
                                         sizeof(missed_call_icon));  
                  }
                  (void) ICONFIG_SetItem(pMe->m_pConfig,
                                         CFGI_RECENT_MO_CALL_TIMER,
                                         &value,
                                         sizeof(uint32));
                  (void) ICONFIG_SetItem(pMe->m_pConfig,
                                         CFGI_RECENT_MT_CALL_TIMER,
                                         &value,
                                         sizeof(uint32));
                  (void) ICONFIG_SetItem(pMe->m_pConfig,
                                         CFGI_ALL_CALL_TIMER,
                                         &value,
                                         sizeof(uint32));
                  //ICALLLIST_Release(m_pCallList);
                  //m_pCallList = NULL;
                  ICALLHISTORY_Release(pCallHistory);
                  pCallHistory = NULL;
                }
                else
                {
                  //ICALLLIST_Release(m_pCallList);
                  //m_pCallList = NULL;
                  return TRUE;
                }
          
                // Update ALERT indicator
                {
                    

                    (void) ICONFIG_GetItem(pMe->m_pConfig,
                                           CFGI_ALERT_TYPE,
                                           &alertType,
                                           sizeof(alertType));
                    switch(alertType)
                    {
                        case OEMNV_ALERTTYPE_OFF :
                            //IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_SILENT, ANNUN_STATE_ON);
                            IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_RINGTONE, ANNUN_STATE_RINGTONE_SILENT);
                            break;

                        case OEMNV_ALERTTYPE_RINGER :
                            //IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_RING, ANNUN_STATE_ON);
                            IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_RINGTONE, ANNUN_STATE_RINGTONE_ALERT);
                            break;

                        case OEMNV_ALERTTYPE_VIB :
                            //IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_VIBRATE, ANNUN_STATE_ON);
                            IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_RINGTONE, ANNUN_STATE_RINGTONE_VIBRATOR);
                            break;

                        case OEMNV_ALERTTYPE_VIBRINGER :
                            //IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_ALERT, ANNUN_STATE_ON);
                            IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_RINGTONE, ANNUN_STATE_RINGTONE_VIBRING);
                            break;
                            
                        case OEMNV_ALERTTYPE_VIBANDRINGER :
                            //IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_ALERT, ANNUN_STATE_ON);
                            IANNUNCIATOR_SetField (pMe->m_pIAnn, ANNUN_FIELD_RINGTONE, ANNUN_STATE_RINGTONE_VIBRING);
                            break;

                        default :
                            break;
                    }
                }
            }
            IANNUNCIATOR_SetField(pMe->m_pIAnn, ANNUN_FIELD_ALARM, ANNUN_STATE_ALARM_OFF/*ANNUN_STATE_OFF*/);
            return TRUE;

        case EVT_DIALOG_END:
            return TRUE;

        case EVT_KEY:
            switch(wParam)
            {
                case AVK_CLR:
                    CLOSE_DIALOG(DLGRET_CANCELED)
                    break;

                default:
                    break;
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
} // QuickTest_RestoreFactory_Handler

/*==============================================================================
函数：
       QuickTest_Ringer

说明：
       此函数用于循环播放铃声。

参数：
       pMe [in]：指向QuickTest Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       无。

备注：:
==============================================================================*/
static void QuickTest_Ringer(CQuickTest *pMe)
{
   IRINGERMGR_Stop(pMe->m_pRingerMgr);
   IRINGERMGR_Play(pMe->m_pRingerMgr, 1, 0);
   (void)ISHELL_SetTimer(pMe->m_pShell,
                         10000,
                         (PFNNOTIFY)(QuickTest_Ringer),
                         pMe);
}//end QuickTest_Ringer

/*==============================================================================
函数：
       QuickTest_Vibrate

说明：
       此函数使手机处在振动状态。

参数：
       pMe [in]：指向QuickTest Applet对象结构的指针。该结构包含小程序的特定信息。

返回值：
       无。

备注：:
==============================================================================*/
static void QuickTest_Vibrate(CQuickTest *pMe)
{
    static boolean vib = FALSE;

    // Alternate between vibrating and not
    vib = !vib;
    if( vib )
    {
        ISOUND_Vibrate(pMe->m_pISound, 5000);
        (void)ISHELL_SetTimer(pMe->m_pShell,
                             5000,
                             (PFNNOTIFY)(QuickTest_Vibrate),
                             pMe);
    }
    else
    {
        ISOUND_StopVibrate(pMe->m_pISound);
        (void)ISHELL_SetTimer(pMe->m_pShell,
                             2000,
                             (PFNNOTIFY)(QuickTest_Vibrate),
                             pMe);
    }
}//end QuickTest_Vibrate

/*==================================================================================================
FUNCTION quicktest_ChangeColor
DISCRIPTION：更换LCD的颜色
PARAMETERS:
          *pMe: CCameraMenu object pointer
RETURN VALUE:

COMMENTS:

SIDE EFFECTS:

SEE ALSO:
===================================================================================================*/
static void quicktest_ChangeColor(void *pme)
{
    CQuickTest     *pMe =(CQuickTest *)pme;
    AEERect        dlgrc;
    int16          nResID;
    uint32         clrFill;
    AECHAR         string[MAX_STRING_LENGTH+1];

    SETAEERECT(&dlgrc,
               0,
               0,
               pMe->m_rc.dx,
               pMe->m_rc.dy);

    MEMSET(string, 0, sizeof(string));

    switch(pMe->colorMask)
    {
        case 0:
            nResID  = IDS_RED;
            clrFill = MAKE_RGB(255, 0, 0);
            pMe->colorMask++;
            break;

        case 1:
            nResID  = IDS_YELLOW;
            clrFill = MAKE_RGB(255, 255, 0);
            pMe->colorMask++;
            break;

        case 2:
            nResID  = IDS_GREEN;
            clrFill = MAKE_RGB(0, 255, 0);
            pMe->colorMask++;
            break;

        case 3:
            nResID  = IDS_BLUE;
            clrFill = MAKE_RGB(0, 0, 255);
            pMe->colorMask++;
            break;

        case 4:
            nResID  = IDS_PURPLE;
            clrFill = MAKE_RGB(255, 0, 255);
            pMe->colorMask++;
            break;

        case 5:
            nResID  = IDS_WHITE;
            clrFill = MAKE_RGB(255, 255, 255);
            pMe->colorMask++;
            break;

        case 6:
            pMe->colorMask = 0;
            quicktest_DrawSevenColor(pMe);
            return;

        default:
            return;
    }


    (void)ISHELL_LoadResString(pMe->m_pShell,
                               AEE_QUICKTEST_RES_FILE,
                               nResID,
                               string,
                               MAX_STRING_LENGTH);

    (void)IDISPLAY_FillRect(pMe->m_pDisplay,
                            &dlgrc,
                            clrFill);
    {
        char temp_str[20];
        int  str_len=WSTRLEN(string);

        SPRINTF(temp_str, " 0x%08X", clrFill);
        STR_TO_WSTR(temp_str,string+str_len,sizeof(string)-str_len*2);
    }
    (void)DrawTextWithProfile(pMe->m_pShell,
                            pMe->m_pDisplay,
                            MAKE_RGB(0xFF, 0xE0, 0xFF),//white but not tansparent
                            AEE_FONT_BOLD,
                            string,
                            -1,
                            0,
                            0,
                            &dlgrc,
                            IDF_ALIGN_CENTER|IDF_ALIGN_MIDDLE
                            |IDF_TEXT_TRANSPARENT);
    IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);

    (void)ISHELL_SetTimer(pMe->m_pShell,
                          1000,
                          (PFNNOTIFY)(quicktest_ChangeColor),
                          pMe);
}//end quicktest_ChangeColor

/*==================================================================================================
FUNCTION quicktest_DrawSevenColor
DISCRIPTION：画出七种颜色的对比图
PARAMETERS:
          *pMe: CCameraMenu object pointer
RETURN VALUE:

COMMENTS:

SIDE EFFECTS:

SEE ALSO:
===================================================================================================*/
static void quicktest_DrawSevenColor(CQuickTest *pme)
{
    AEERect        dlgrc;
    AEERect        rc;
    uint32         color[7] = {MAKE_RGB(255, 0, 0),
                               MAKE_RGB(255, 255, 0),
                               MAKE_RGB(0, 255, 0),
                               MAKE_RGB(0, 0, 255),
                               MAKE_RGB(255, 0, 255),
                               MAKE_RGB(255, 255, 255),
                               MAKE_RGB(0, 0, 0)};
    int            i;

    SETAEERECT(&dlgrc,
               0,
               0,
               pme->m_rc.dx,
               pme->m_rc.dy);

    for (i=0; i<6; i++)
    {
        SETAEERECT(&rc,
                   dlgrc.x + i * (dlgrc.dx/7),
                   dlgrc.y,
                   dlgrc.dx/7,
                   dlgrc.dy);
        IDISPLAY_FillRect(pme->m_pDisplay,
                          &rc,
                          color[i]);
    }

    SETAEERECT(&rc,
               dlgrc.x + 6 * (dlgrc.dx/7),
               dlgrc.y,
               dlgrc.dx - 6 * (dlgrc.dx/7),
               dlgrc.dy);
    IDISPLAY_FillRect(pme->m_pDisplay,
                      &rc,
                      color[6]);

    IDISPLAY_UpdateEx(pme->m_pDisplay, FALSE);
}//end quicktest_DrawSevenColor

/*=============================================================================
FUNCTION: quicktest_mic_receiver_Loopback

DESCRIPTION: test mic and receiver loopback for call test

RETURN VALUE:none

COMMENTS:

SIDE EFFECTS:

SEE ALSO:

=============================================================================*/
static void quicktest_mic_receiver_Loopback(CQuickTest *pMe)
{
    //For mic-receiver test
    AECHAR           string[20];
    AEESoundInfo     soundStuff;
    boolean headsetPresent;

    if (SUCCESS != ICONFIG_GetItem(pMe->m_pConfig,
                                    CFGI_HEADSET_PRESENT,
                                    &headsetPresent,
                                    sizeof(headsetPresent)))
    {
        headsetPresent = FALSE;
    }

    IDISPLAY_ClearScreen(pMe->m_pDisplay);
    if(headsetPresent)
    {
        STRTOWSTR("headset loop",string,sizeof(string));
        soundStuff.eDevice = AEE_SOUND_DEVICE_STEREO_HEADSET; //AEE_SOUND_DEVICE_HEADSET;
    }
    else
    {
        STRTOWSTR("HANDSET LOOP",string,sizeof(string));
        soundStuff.eDevice = AEE_SOUND_DEVICE_HANDSET;
    }
    (void)IDISPLAY_DrawText(pMe->m_pDisplay,
                            AEE_FONT_BOLD,
                            string,
                            -1,
                            0,
                            0,
                            NULL,
                            IDF_ALIGN_CENTER);
    IDISPLAY_UpdateEx(pMe->m_pDisplay, FALSE);
    soundStuff.eMethod = AEE_SOUND_METHOD_VOICE;
    soundStuff.eAPath = AEE_SOUND_APATH_BOTH;
    soundStuff.eEarMuteCtl = AEE_SOUND_MUTECTL_UNMUTED;
    soundStuff.eMicMuteCtl = AEE_SOUND_MUTECTL_UNMUTED;
    (void) ISOUND_Set(pMe->m_pISound, &soundStuff);
    ISOUND_SetDevice(pMe->m_pISound);
    ISOUND_SetVolume(pMe->m_pISound,GET_ISOUND_VOL_LEVEL(OEMSOUND_4TH_VOL));
#ifndef WIN32
    //Config the vocoder
    voc_acquire(VOC_ACQ_TEST, NULL);
    voc_config(VOC_ACQ_TEST, VOC_CAP_IS127);
    //Reset the qdsp interrupt handle function
    qdsp_cmd_set_isr( iquicktest_mic_receiver_loopback_isr );
#endif
}


#if defined( FEATURE_FM_RADIO)

static void convertChannelValueToText( int channel, AECHAR *textBuffer, int bufferSizeInBytes)
{
    AECHAR  format[]    = { 'F', 'M', ' ', '%', 'd', '.', '%', 'd', ' ', 'M', 'H', 'z', 0};
    uint32  iFreqInt    = 0;              //频率的整数部分
    uint32  iFreqFra    = 0;              //频率的小数部分

    iFreqInt = ( CHANNEL_SPACE * channel);
    iFreqFra = ( iFreqInt % 1000) / 100;
    iFreqInt /= 1000;
    WSPRINTF( textBuffer, bufferSizeInBytes, format, iFreqInt, iFreqFra);
}

static int convertChannelValueFromText( AECHAR *textBuffer)
{

    AECHAR  text[16]    = {0};
    int     integral    = 0;
    int     fraction    = 0;
    int     result      = 0;

    int     length      = WSTRLEN( textBuffer);
    AECHAR* fractionStr = WSTRCHR( textBuffer, (AECHAR)'.');

    WSTRLCPY( text, textBuffer, fractionStr == NULL ? length + 1 : fractionStr - textBuffer + 1);
    integral = WSTRTOFLOAT( text);
    fraction = fractionStr == NULL ? 0 : WSTRTOFLOAT( ++ fractionStr);

    result = ( integral * 1000 + fraction * 100 - LOWEST_BAND_FREQ) / CHANNEL_SPACE;

    ERR("result = %d",result,0,0);
    return result;
}

static void quicktest_fm_init( CQuickTest* pMe)
{

    pMe->m_bAppIsReady              = FALSE;
#ifndef WIN32
    pMe->m_fmIsPowerupBeforeFmTest  = fm_radio_is_power_up();

    if( pMe->m_fmIsPowerupBeforeFmTest)
    {
        pMe->m_fmChannelBeforeFmTest = fm_radio_get_playing_channel();
    }

    if( !fm_radio_is_inited())
    {
        fm_radio_init();
    }
#endif
    ISHELL_SetTimer( pMe->m_pShell, 1000, quicktest_fm_power_up, (void*)pMe);
}

static void quicktest_fm_power_up( void* pme)
{

    CQuickTest* pMe                 = (CQuickTest*)pme;
    AECHAR      defaultChannel[]    = { '9', '8', '.', '5', 0};
#ifndef WIN32
    if( !fm_radio_is_power_up())
    {
        fm_radio_power_up();
    }
	if (HS_HEADSET_ON())
	{
		fm_mute(FALSE);
	}		    
    fm_set_volume(7);
#endif
    quicktest_fm_set_channel_to( pMe, convertChannelValueFromText( defaultChannel));

    pMe->m_bAppIsReady = TRUE;
}


static void quicktest_fm_set_channel_to( CQuickTest* pMe, uint16 theNewChannel)
{
#ifndef WIN32
    fm_tune_channel( theNewChannel);
#endif
    quicktest_fm_paint( pMe);
}

static void quicktest_fm_paint( CQuickTest* pMe)
{

    IDISPLAY_ClearScreen( pMe->m_pDisplay);

    if( pMe->m_bAppIsReady)
    {

        AECHAR text[][32] = {
                { 0},
                { 'L', 'E', 'F', 'T', ',', 'R', 'I', 'G', 'H', 'T', ':', ' ', 'm', 'a', 'n', 'u', 'a', 'l', 0},
                { 'U', 'P', ',', 'D', 'O', 'W', 'N', ':', ' ', 'm', 'a', 'n', 'u', 'a', 'l', 0}
        };
        int i = 0;
        int y = 40;
#ifndef WIN32
        convertChannelValueToText( fm_radio_get_playing_channel(), text[0], 32);
#else
        convertChannelValueToText( channel, text[0], 32);
#endif
        for( i = 0; i < 3; i ++)
        {
            IDISPLAY_DrawText( pMe->m_pDisplay,
                        AEE_FONT_NORMAL,
                        text[i],
                        -1,
                        0,
                        y,
                        NULL,
                        IDF_ALIGN_CENTER | IDF_TEXT_TRANSPARENT
                    );
            y += 16;
        }
    }
    else
    {

        AECHAR text[] = { 'F', 'M', ' ', 'p', 'l', 'a', 'y','i', 'n', 'g', '.', '.', 0};
        IDISPLAY_DrawText( pMe->m_pDisplay,
                    AEE_FONT_NORMAL,
                    text,
                    -1,
                    0,
                    57,
                    NULL,
                    IDF_ALIGN_CENTER | IDF_TEXT_TRANSPARENT
                );
    }

    IDISPLAY_Update( pMe->m_pDisplay);
}

#endif

#ifdef FEATURE_LED_CONTROL
/*===========================================================================

FUNCTION disp_set_sigled_cmd

DESCRIPTION
  This function is used by the client to switch the display sig led on or off

DEPENDENCIES

RETURN VALUE

SIDE EFFECTS
  None

===========================================================================*/
static int disp_set_sigled_cmd(hs_sig_led_onoff_type onoff)
{
    hs_sig_led_prf_type sig_led_prf_handle;
    int nErr = SUCCESS;
    sig_led_prf_handle.onoff = onoff;
    if (!sig_led_prf_contrl(sig_led_prf_handle, onoff)) 
    {
        nErr = EFAILED;
    }
    
    return nErr;
}
#endif

