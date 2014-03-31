.386
.model flat, stdcall
option casemap: none

INCLUDE TinyThief.inc



;----------------------------------------------------------------

;代码段

;----------------------------------------------------------------
.code



;播放mp3文件
PlayMp3File proc hWin:DWORD,NameOfFile:DWORD

      local mciOpenParms:MCI_OPEN_PARMS,mciPlayParms:MCI_PLAY_PARMS

            mov eax,hWin        
            mov mciPlayParms.dwCallback,eax
            mov eax,OFFSET Mp3Device
            mov mciOpenParms.lpstrDeviceType,eax
            mov eax,NameOfFile
            mov mciOpenParms.lpstrElementName,eax
            INVOKE mciSendCommand,0,MCI_OPEN,MCI_OPEN_TYPE or MCI_OPEN_ELEMENT,ADDR mciOpenParms
            mov eax,mciOpenParms.wDeviceID
            mov Mp3DeviceID,eax
            INVOKE mciSendCommand,Mp3DeviceID,MCI_PLAY,MCI_NOTIFY,ADDR mciPlayParms
            ret  

PlayMp3File endp

;窗口过程
_ProcWinMain proc uses ebx edi esi, hWnd, uMsg, wParam, lParam
		local @stPs:PAINTSTRUCT
		local @stRect:RECT
		local @stPos:POINT
		local @hSysMenu

		.IF uMsg == WM_CREATE
			
			;INVOKE GetSubMenu, hMenu, 1
			;mov hSubMenu, eax
			;INVOKE GetSystemMenu, hWnd, FALSE
			;mov @hSysMenu, eax
			;INVOKE AppendMenu, @hSysMenu, MF_SEPARATOR, 0, NULL
			;INVOKE AppendMenu, @hSysMenu, 0, IDM_HELP, offset szMenuHelp
			INVOKE InitItemList
			INVOKE SetTimer, hWnd, 1001, 50, NULL
		.ELSEIF uMsg == WM_TIMER						;计时器事件
			INVOKE JudgeCollisions
			INVOKE ThiefMove
			;INVOKE MessageBox, NULL, addr szText, addr szCaption, MB_OK
			INVOKE InvalidateRect, hWnd, NULL, FALSE
		.ELSEIF uMsg == WM_PAINT						;绘制事件
			INVOKE BeginPaint, hWnd, addr @stPs
			mov hdc, eax
			
			INVOKE CreateCompatibleDC,hdc
			mov hdcMem, eax
			INVOKE CreateCompatibleDC,hdc
			mov hdcImage, eax
			INVOKE CreateCompatibleBitmap,hdc, SCREEN_X, SCREEN_Y
			mov bmp, eax

			INVOKE SelectObject,hdcMem,bmp

			INVOKE DrawProc
			
			INVOKE BitBlt,hdc,0,0,800,600,hdcMem,0,0,SRCCOPY
			INVOKE DeleteObject,bmp
			INVOKE DeleteDC,hdcImage
			INVOKE DeleteDC,hdcMem
			INVOKE EndPaint, hWnd, addr @stPs
		.ELSEIF uMsg == WM_KEYDOWN						;键盘事件
			;INVOKE InvalidateRect, hWnd, NULL, FALSE
		.ELSEIF uMsg == WM_LBUTTONDOWN					;鼠标事件
			;.IF cClick == 0
			;	ret
			;.ENDIF
			INVOKE GetWindowRect, hWnd, ADDR @stRect
			INVOKE GetCursorPos, ADDR @stPos
			mov edx, @stPos.x
			sub edx, @stRect.left
			sub edx, 32
			mov Click_X, edx
			
			.IF Click_X > 800
				mov Click_X, 0
			.ENDIF
			
			mov edx, @stPos.y
			sub edx, 130
			mov Click_Y, edx

			mov ebx, Click_X
			.IF ebx > Thief_X
				mov Orientation, 0
			.ELSEIF ebx < Thief_X
				mov Orientation, 1
			.ENDIF
			INVOKE processMouseEvent, Scenario
		.ELSEIF uMsg == WM_CLOSE
			INVOKE KillTimer, hWnd, 1
			INVOKE DestroyWindow, hWinMain
			INVOKE PostQuitMessage, NULL
			INVOKE ExitProcess, NULL
		.ELSE
				INVOKE DefWindowProc, hWnd, uMsg, wParam, lParam
				ret
		.ENDIF
		xor eax, eax
		ret
				
_ProcWinMain endp

_WinMain proc
		local @stWndClass:WNDCLASSEX
		local @stMsg:MSG

		INVOKE GetModuleHandle, NULL
		mov hInstance, eax
		;INVOKE LoadMenu, hInstance, IDM_MAIN
		;mov hMenu, eax
		INVOKE RtlZeroMemory, addr @stWndClass, sizeof @stWndClass
		

		;注册窗口类
		;INVOKE LoadIcon, 0, 200
		INVOKE LoadIcon, hInstance, 1000
		mov @stWndClass.hIcon, eax
		mov @stWndClass.hIconSm, eax
		INVOKE LoadCursor, 0, IDC_ARROW
		mov @stWndClass.hCursor, eax
		push hInstance
		pop @stWndClass.hInstance
		mov @stWndClass.cbSize, sizeof WNDCLASSEX
		mov @stWndClass.style, 0
		mov @stWndClass.lpfnWndProc, offset _ProcWinMain
		mov @stWndClass.hbrBackground, COLOR_WINDOW + 1
		mov @stWndClass.lpszClassName, offset szClassName
		INVOKE RegisterClassEx, addr @stWndClass

		;建立并显示窗口
		INVOKE CreateWindowEx, WS_EX_CLIENTEDGE,\
				offset szClassName, offset szCaptionMain,\
				WS_OVERLAPPEDWINDOW,\
				100, 100, SCREEN_X, SCREEN_Y,\
				NULL, hMenu, hInstance, NULL
		mov hWinMain, eax
		INVOKE ShowWindow, hWinMain, SW_SHOWNORMAL
		INVOKE UpdateWindow, hWinMain
                                
		;INVOKE PlayMp3File,hWinMain,ADDR MusicName

		;消息循环
		.WHILE TRUE
				INVOKE GetMessage, addr @stMsg, NULL, 0, 0
				;.IF eax == 0
				;	INVOKE ExitProcess, NULL
				;.ENDIF
				INVOKE TranslateMessage, addr @stMsg
				INVOKE DispatchMessage, addr @stMsg
		.ENDW
		ret
_WinMain	endp

start:
			INVOKE _WinMain
			INVOKE ExitProcess, NULL

			end start