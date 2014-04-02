
.code

;绘制物品
DrawObject proc bID:DWORD, img:DWORD, xDesc:DWORD, yDesc:DWORD, sWidth:DWORD, sHeight:DWORD


	.IF bID == IMG_30202
		mov xDesc, 198
	.ELSEIF bID == IMG_30302
		mov xDesc, 311
	.ELSEIF bID == IMG_30402
		mov xDesc, 424
	.ENDIF

	INVOKE SelectObject,hdcImage,img
	INVOKE BitBlt,hdcMem,xDesc,yDesc,sWidth,sHeight,hdcImage,0,0,SRCCOPY
	
	ret
DrawObject endp

;绘制背景透明的物品
DrawTransparentObject proc bID:DWORD, img:DWORD, xDesc:DWORD, yDesc:DWORD, sWidth:DWORD, sHeight:DWORD

	INVOKE SelectObject,hdcImage,img

	.IF bID == IMG_30601 || bID == IMG_30602
		mov xDesc, 601
		mov yDesc, 40
	.ELSEIF bID == IMG_30701 || bID == IMG_30702
		mov yDesc, 165
	.ENDIF

	INVOKE BitBlt,hdcMem,xDesc,yDesc,sWidth,sHeight,hdcImage,sWidth,0,SRCAND
	INVOKE BitBlt,hdcMem,xDesc,yDesc,sWidth,sHeight,hdcImage,0,0,SRCPAINT
	
	ret
DrawTransparentObject endp

;绘制盗贼
DrawThief proc 

	.IF Orientation == 0
		.IF Run == 0
			INVOKE DrawTransparentObject, 1111, Thief_right_s_img,Thief_X,Thief_Y,25,32
		.ELSE
			INVOKE DrawTransparentObject, 3333, Thief_right_r_img,Thief_X,Thief_Y,25,32
		.ENDIF
	.ELSEIF Run == 0
		INVOKE DrawTransparentObject, 2222, Thief_left_s_img,Thief_X,Thief_Y,25,32
	.ELSE
		INVOKE DrawTransparentObject, 4444, Thief_left_r_img,Thief_X,Thief_Y,25,32
	.ENDIF

    ret

DrawThief endp

;绘制背景
DrawBackground proc
	.IF Scenario == 0
		INVOKE DrawObject, IMG_0, (ItemList[IMG_0*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 1
		INVOKE DrawObject, IMG_1, (ItemList[IMG_1*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 2
		INVOKE DrawObject, IMG_2, (ItemList[IMG_2*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 3
		INVOKE DrawObject, IMG_300, (ItemList[IMG_300*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 4
		INVOKE DrawObject, IMG_400, (ItemList[IMG_400*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ENDIF
	ret
DrawBackground endp

;绘制其余物品
DrawItems proc
	local i:DWORD
	mov i, 0
	mov ebx, i
	mov eax, pSequence[ebx]
	.WHILE eax != -1
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		mov cl, (ItemList[eax]).pMethod
		.IF cl == 0
			INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ELSE
			INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ENDIF
		add i, 4
		mov ebx, i
		mov eax, pSequence[ebx]

	.ENDW
	ret
DrawItems endp

;绘制Icons
DrawIcons proc
	local i:DWORD
	mov i, 0
	mov ebx, i
	mov eax, drawIcon[ebx]
	.WHILE eax != -1 && i < 20
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		mov cl, (ItemList[eax]).pMethod
		.IF cl == 0
			INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ELSE
			INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ENDIF
		add i, 4
		mov ebx, i
		mov eax, drawIcon[ebx]

	.ENDW
	ret
DrawIcons endp

;绘制提示
DrawPassBy proc
	.IF PassBy == -1
		ret
	.ENDIF
	mov eax, PassBy
	mov esi, eax
	mov edx, TYPE MyItem
	mul edx
	mov cl, (ItemList[eax]).pMethod
	.IF cl == 0
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ELSE
		INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF
	ret
DrawPassBy endp

DrawProc proc

	INVOKE DrawBackground
	.IF Scenario == 4
		INVOKE DrawIcons
	.ENDIF
	.IF Scenario > 2
		INVOKE DrawItems
		INVOKE DrawPassBy
		.IF pThief == 1
			INVOKE DrawThief
		.ENDIF
	.ENDIF
    ret

DrawProc endp

