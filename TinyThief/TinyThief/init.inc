;-----------------------------------------------------------|
;															|
;		本文件用于对游戏中所有物体进行初始化				|
;															|
;___________________________________________________________|
.code

;初始化一个Item
InitItem proc id:DWORD, iwidth:DWORD, iheight:DWORD, x1:DWORD, y1:DWORD, x2:DWORD, y2:DWORD, pMethod:BYTE, eClick:BYTE
	local count:DWORD

	mov eax, id
	mov ebx, TYPE MyItem
	mul ebx
	mov count, eax
	INVOKE LoadBitmap, hInstance, id
	mov ecx, count
	mov (MyItem PTR ItemList[ecx]).img, eax
	mov ebx, iwidth
	mov (MyItem PTR ItemList[ecx]).iwidth, ebx
	mov ebx, iheight
	mov (MyItem PTR ItemList[ecx]).iheight, ebx
	mov ebx, x1
	mov (MyItem PTR ItemList[ecx]).x1, ebx
	mov ebx, y1
	mov (MyItem PTR ItemList[ecx]).y1, ebx
	mov ebx, x2
	mov (MyItem PTR ItemList[ecx]).x2, ebx
	mov ebx, y2
	mov (MyItem PTR ItemList[ecx]).y2, ebx
	mov bl, pMethod
	mov (MyItem PTR ItemList[ecx]).pMethod, bl
	mov bl, eClick
	mov (MyItem PTR ItemList[ecx]).eClick, bl
	
	ret

InitItem endp

;初始化所有的Item
InitItemList proc
	
	INVOKE InitItem, IMG_0, 0, 0, 0, 0, 0, 0, 0, 1
	INVOKE InitItem, IMG_1, 0, 0, 0, 0, 0, 0, 0, 1
	INVOKE InitItem, IMG_2, 0, 0, 0, 0, 0, 0, 0, 1
		
	INVOKE InitItem, IMG_400, 0, 0, 0, 0, 0, 0, 0, 1
	INVOKE InitItem, IMG_400, 0, 0, 0, 0, 0, 0, 0, 1
	INVOKE InitItem, IMG_401, 65, 143, 74, 43, 139, 96, 0, 1
	INVOKE InitItem, IMG_402, 65, 143, 194, 43, 259, 96, 0, 1
	INVOKE InitItem, IMG_403, 65, 143, 309, 39, 374, 93, 0, 1
	INVOKE InitItem, IMG_404, 65, 143, 658, 39, 723, 93, 0, 1
	INVOKE InitItem, IMG_405, 65, 143, 79, 185, 144, 240, 0, 1
	INVOKE InitItem, IMG_406, 65 ,143, 197, 185, 262, 236, 0, 1
	INVOKE InitItem, IMG_407, 65, 143, 368, 229, 433, 282, 1, 1
	INVOKE InitItem, IMG_408, 65, 143 ,545, 183, 610, 235, 0, 1
	INVOKE InitItem, IMG_409, 65, 143, 660, 181, 725, 235, 0, 1
	INVOKE InitItem, IMG_410, 65, 143, 92, 404, 157, 457, 0, 1
	INVOKE InitItem, IMG_411, 65, 143, 214, 405, 279, 457, 0, 1
	INVOKE InitItem, IMG_412, 65, 143, 424, 401, 489, 454, 0, 1
	INVOKE InitItem, IMG_413, 65, 143, 536, 398, 601, 454, 0, 1
	INVOKE InitItem, IMG_414, 65, 143, 652, 399, 717, 451, 0, 1
	INVOKE InitItem, IMG_415, 65, 44, 383, 216, 448, 260, 0, 1
	INVOKE InitItem, IMG_416, 65, 44, 277, 397, 342, 441, 0, 1
	INVOKE InitItem, IMG_417, 65, 44, 637, 359, 702, 403, 0, 1
	INVOKE InitItem, IMG_418, 65, 44, 114, 359, 179, 403, 0, 1
	INVOKE InitItem, IMG_419, 65, 44, 292, 283, 357, 327, 0, 1
	INVOKE InitItem, IMG_42001, 61, 91, 493, 73, 554, 126, 0, 1
	INVOKE InitItem, IMG_42002, 61, 91, 493, 73, 554, 126, 0, 0
	INVOKE InitItem, IMG_42101, 62, 109, 319, 438, 381, 491, 0, 0
	INVOKE InitItem, IMG_42102, 62, 109, 319, 438, 381, 491, 0, 1
	INVOKE InitItem, IMG_42103, 62, 109, 319, 438, 381, 491, 0, 0
	INVOKE InitItem, IMG_42104, 62, 109, 319, 438, 381, 491, 0, 0
	INVOKE InitItem, IMG_422, 39, 39, 750, 547, 0, 0, 1, 0
		
	INVOKE InitItem, IMG_300, 0, 0, 0, 0, 0, 0, 0, 1
	INVOKE InitItem, IMG_301, 93, 101, 45, 61, 138, 162, 0, 0
	INVOKE InitItem, IMG_30201, 105, 149, 198, 41, 303, 190, 0, 0
	INVOKE InitItem, IMG_30202, 105, 149, 222, 41, 279, 95, 0, 1
	INVOKE InitItem, IMG_30301, 105, 149, 311, 36, 416, 185, 0, 0
	INVOKE InitItem, IMG_30302, 105, 149, 333, 36, 395, 93, 0, 1
	INVOKE InitItem, IMG_30401, 105, 149, 424, 34, 529, 183, 0, 0
	INVOKE InitItem, IMG_30402, 105, 149, 444, 34, 508, 90, 0, 1
	INVOKE InitItem, IMG_305, 45, 133, 543, 46, 587, 179, 0, 0
	INVOKE InitItem, IMG_30601, 148, 451, 610, 40, 677, 94, 1, 1	
	INVOKE InitItem, IMG_30602, 148, 451, 685, 354, 746, 407, 1, 1
	INVOKE InitItem, IMG_30701, 111, 138, 635, 190, 690, 244, 1, 1	
	INVOKE InitItem, IMG_30702, 111, 138, 635, 204, 690, 257, 1, 1
		
	INVOKE InitItem, IMG_500, 0, 0, 0, 0, 0, 0, 0, 1
	INVOKE InitItem, IMG_501, 490, 406, 52, 78, 0, 0, 1, 0
	INVOKE InitItem, IMG_5020101, 305, 305, 138, 140, 0, 0, 0, 0
	INVOKE InitItem, IMG_5020102, 305, 305, 138, 140, 0, 0, 0, 0
	INVOKE InitItem, IMG_5020103, 305, 305, 138, 140, 0, 0, 0, 0
	INVOKE InitItem, IMG_5020104, 305, 305, 138, 140, 0, 0, 0, 0
	INVOKE InitItem, IMG_5020201, 305, 305, 138, 140, 0, 0, 1, 0
	INVOKE InitItem, IMG_5020202, 305, 305, 138, 140, 0, 0, 1, 0
	INVOKE InitItem, IMG_5020203, 305, 305, 138, 140, 0, 0, 1, 0
	INVOKE InitItem, IMG_5020204, 305, 305, 138, 140, 0, 0, 1, 0
	INVOKE InitItem, IMG_5020301, 305, 305, 138, 140, 0, 0, 1, 0
	INVOKE InitItem, IMG_5020302, 305, 305, 138, 140, 0, 0, 1, 0
	INVOKE InitItem, IMG_5020303, 305, 305, 138, 140, 0, 0, 1, 0
	INVOKE InitItem, IMG_5020304, 305, 305, 138, 140, 0, 0, 1, 0
	INVOKE InitItem, IMG_503, 62, 140, 89, 397, 151, 450, 0, 1
	INVOKE InitItem, IMG_504, 56, 110, 214, 427, 270, 480, 1, 1
	INVOKE InitItem, IMG_505, 56, 110, 297, 426, 353, 478, 1, 1
	INVOKE InitItem, IMG_506, 56, 110, 383, 425, 439, 477, 0, 1
	INVOKE InitItem, IMG_507, 48, 114, 553, 419, 0, 0, 0, 0
	INVOKE InitItem, IMG_50801, 57, 108, 629, 421, 686, 473, 0, 1
	INVOKE InitItem, IMG_50802, 57, 108, 629, 421, 0, 0, 0, 0
	INVOKE InitItem, IMG_50901, 56, 97, 686, 451, 741, 500, 0, 1
	INVOKE InitItem, IMG_50902, 56, 97, 686, 451, 741, 500, 0, 1
	INVOKE InitItem, IMG_50903, 56, 97, 686, 404, 0, 0, 0, 0
	INVOKE InitItem, IMG_50904, 56, 97, 686, 404, 741, 459, 0, 1
	INVOKE InitItem, IMG_50905, 56, 97, 682, 433, 0, 0, 0, 1
	INVOKE InitItem, IMG_50906, 56, 97, 686, 404, 0, 0, 0, 0
	INVOKE InitItem, IMG_510, 39, 39, 700, 547, 0, 0, 1, 0

	INVOKE InitItem, IMG_90101, 150, 350, 0, 30, 0, 0, 1, 0
	INVOKE InitItem, IMG_90102, 150, 350, 0, 30, 0, 0, 1, 0
	INVOKE InitItem, IMG_90200, 261, 123, 270, 13, 0, 0, 1, 0
	INVOKE InitItem, IMG_90201, 26, 26, 290, 54, 0, 0, 0, 0
	INVOKE InitItem, IMG_90202, 26, 26, 304, 28, 0, 0, 0, 0
	INVOKE InitItem, IMG_90203, 26, 26, 318, 54, 0, 0, 0, 0
	INVOKE InitItem, IMG_90204, 24, 23, 306, 78, 0, 0, 0, 0
	INVOKE InitItem, IMG_90205, 78, 95, 360, 27, 0, 0, 1, 0
	INVOKE InitItem, IMG_90206, 49, 67, 460, 33, 0, 0, 0, 0
		
	INVOKE InitItem, IMG_600, 0, 0, 0, 0, 0, 0, 0, 1
	INVOKE InitItem, IMG_601, 62, 138, 632, 404, 694, 459, 0, 1
	INVOKE InitItem, IMG_60201, 69, 112, 478, 434, 535, 489, 1, 1
	INVOKE InitItem, IMG_60202, 69, 112, 478, 434, 0, 0, 1, 0
	INVOKE InitItem, IMG_60301, 69, 112, 384, 434, 439, 488, 0, 1
	INVOKE InitItem, IMG_60302, 69, 112, 384, 434, 0, 0, 0, 0
	INVOKE InitItem, IMG_60401, 69, 112, 295, 438, 350, 491, 0, 1
	INVOKE InitItem, IMG_60402, 69, 112, 295, 438, 0, 0, 0, 0
	INVOKE InitItem, IMG_60501, 69, 112, 201, 438, 257, 491, 0, 1
	INVOKE InitItem, IMG_60502, 69, 112, 201, 438, 0, 0, 0, 0
	INVOKE InitItem, IMG_60601, 96, 92, 42, 461, 0, 0, 0, 0
	INVOKE InitItem, IMG_60602, 96, 92, 42, 461, 0, 0, 0, 0
	INVOKE InitItem, IMG_60603, 96, 92, 42, 461, 0, 0, 0, 0
	INVOKE InitItem, IMG_60604, 96, 92, 42, 461, 0, 0, 0, 0
	INVOKE InitItem, IMG_60605, 96, 92, 42, 461, 0, 0, 0, 0
	INVOKE InitItem, IMG_60701, 345, 306, 123, 66, 0, 0, 0, 0
	INVOKE InitItem, IMG_60702, 65, 83, 153, 285, 0, 0, 0, 0
	INVOKE InitItem, IMG_60703, 345, 306, 123, 66, 0, 0, 0, 0
	INVOKE InitItem, IMG_60801, 210, 358, 162, 74, 0, 0, 0, 0
	INVOKE InitItem, IMG_60802, 68, 80, 285, 351, 0, 0, 0, 0
	INVOKE InitItem, IMG_60803, 210, 358, 162, 74, 0, 0, 0, 0
	INVOKE InitItem, IMG_60901, 252, 329, 384, 65, 0, 0, 0, 0
	INVOKE InitItem, IMG_60902, 68, 83, 415, 311, 0, 0, 0, 0
	INVOKE InitItem, IMG_60903, 252, 329, 384, 65, 0, 0, 0, 0
	INVOKE InitItem, IMG_61001, 329, 278, 317, 66, 0, 0, 0, 0
	INVOKE InitItem, IMG_61002, 68, 81, 553, 263, 0, 0, 0, 0
	INVOKE InitItem, IMG_61003, 329, 278, 317, 66, 0, 0, 0, 0
	INVOKE InitItem, IMG_61101, 53, 109, 353, 440, 0, 0, 0, 0
	INVOKE InitItem, IMG_61102, 53, 109, 353, 440, 406, 495, 0, 1
	INVOKE InitItem, IMG_612, 39, 39, 650, 547, 0, 0, 1, 0
	INVOKE InitItem, IMG_61301, 58, 91, 44, 438, 102, 490, 0, 1
	INVOKE InitItem, IMG_61302, 58, 91, 44, 438, 0, 0, 0, 0
	INVOKE InitItem, IMG_61401, 65, 121, 449, 427, 0, 0, 0, 0
	INVOKE InitItem, IMG_61402, 65, 121, 449, 427, 514, 480, 0, 1
	INVOKE InitItem, IMG_61403, 65, 121, 449, 427, 0, 0, 0, 0
	INVOKE InitItem, IMG_61404, 65, 121, 449, 427, 0, 0, 0, 0

	INVOKE InitItem, IMG_30801, 104, 106, 613, 193, 667, 246, 0, 1
	INVOKE InitItem, IMG_30802, 104, 106, 613, 193, 0, 0, 0, 0
	INVOKE InitItem, IMG_30803, 104, 106, 633, 193, 688, 246, 0, 1
	INVOKE InitItem, IMG_30804, 104, 106, 613, 193, 0, 0, 0, 0
	INVOKE InitItem, IMG_30805, 104, 106, 656, 193, 710, 246, 0, 1
	INVOKE InitItem, IMG_30806, 104, 106, 613, 193, 0, 0, 0, 0
	INVOKE InitItem, IMG_30901, 426, 363, 173, 193, 0, 0, 0, 0
	INVOKE InitItem, IMG_30902, 426, 363, 173, 193, 0, 0, 0, 0
	INVOKE InitItem, IMG_30903, 426, 363, 173, 193, 0, 0, 0, 0
	INVOKE InitItem, IMG_30904, 426, 363, 173, 193, 0, 0, 0, 0
	INVOKE InitItem, IMG_30905, 426, 363, 173, 193, 0, 0, 0, 0
	INVOKE InitItem, IMG_310, 59, 102, 358, 446, 417, 499, 0, 1
	INVOKE InitItem, IMG_31101, 40, 38, 234, 502, 274, 540, 0, 1
	INVOKE InitItem, IMG_31102, 40, 38, 234, 502, 274, 540, 0, 1
	INVOKE InitItem, IMG_31103, 40, 38, 234, 502, 274, 540, 0, 1
	INVOKE InitItem, IMG_31201, 40, 38, 369, 502, 409, 540, 0, 1
	INVOKE InitItem, IMG_31202, 40, 38, 369, 502, 409, 540, 0, 1
	INVOKE InitItem, IMG_31203, 40, 38, 369, 502, 409, 540, 0, 1
	INVOKE InitItem, IMG_31301, 40, 38, 501, 502, 541, 540, 0, 1
	INVOKE InitItem, IMG_31302, 40, 38, 501, 502, 541, 540, 0, 1
	INVOKE InitItem, IMG_31303, 40, 38, 501, 502, 541, 540, 0, 1
	INVOKE InitItem, IMG_31401, 31, 32, 247, 441, 278, 473, 0, 1
	INVOKE InitItem, IMG_31402, 31, 32, 287, 441, 318, 473, 0, 1
	INVOKE InitItem, IMG_31403, 31, 32, 326, 441, 357, 473, 0, 1
	INVOKE InitItem, IMG_31404, 31, 32, 370, 441, 401, 473, 0, 1
	INVOKE InitItem, IMG_31405, 31, 32, 415, 441, 446, 473, 0, 1
	INVOKE InitItem, IMG_31406, 31, 32, 455, 441, 486, 473, 0, 1
	INVOKE InitItem, IMG_31407, 31, 32, 495, 441, 526, 473, 0, 1
	INVOKE InitItem, IMG_315, 31, 40, 370, 441, 401, 473, 0, 1
	INVOKE InitItem, IMG_316, 51, 17, 279, 471, 0, 0, 0, 0
	INVOKE InitItem, IMG_31701, 41, 39, 296, 372, 337, 411, 0, 1
	INVOKE InitItem, IMG_31702, 41, 39, 342, 372, 383, 411, 0, 1
	INVOKE InitItem, IMG_31703, 41, 39, 388, 372, 429, 411, 0, 1
	INVOKE InitItem, IMG_31704, 41, 39, 435, 372, 476, 411, 0, 1
	INVOKE InitItem, IMG_31801, 60, 109, 358, 183, 418, 292, 0, 1
	INVOKE InitItem, IMG_31802, 60, 109, 358, 183, 0, 0, 0, 0
	INVOKE InitItem, IMG_319, 47, 48, 95, 501, 142, 549, 0, 0

	INVOKE InitItem, IMG_700, 297, 377, 250, 111, 0, 0, 1, 0
	INVOKE InitItem, IMG_701, 25, 25, 299, 157, 0, 0, 0, 0
	INVOKE InitItem, IMG_702, 25, 25, 312, 132, 0, 0, 0, 0
	INVOKE InitItem, IMG_703, 25, 25, 327, 158, 0, 0, 0, 0
	INVOKE InitItem, IMG_704, 53, 45, 448, 137, 0, 0, 0, 0
	INVOKE InitItem, IMG_705, 80, 82, 275, 210, 0, 0, 1, 0
	INVOKE InitItem, IMG_706, 80, 82, 444, 208, 0, 0, 1, 0
		
	INVOKE InitItem, IMG_801, 608, 396, 94, 90, 0, 0, 1, 0
	INVOKE InitItem, IMG_802, 608, 396, 94, 90, 0, 0, 1, 0
	INVOKE InitItem, IMG_803, 608, 396, 94, 90, 0, 0, 1, 0
	INVOKE InitItem, IMG_804, 608, 396, 94, 90, 0, 0, 1, 0
	INVOKE InitItem, IMG_805, 608, 396, 94, 90, 0, 0, 1, 0
	INVOKE InitItem, IMG_806, 608, 396, 94, 90, 0, 0, 1, 0
	INVOKE InitItem, IMG_807, 608, 396, 94, 90, 0, 0, 1, 0
	INVOKE InitItem, IMG_808, 608, 396, 94, 90, 0, 0, 1, 0
		
	INVOKE InitItem, IMG_511, 34, 34, 63, 13, 47, 97, 0, 1
	INVOKE InitItem, IMG_320, 44, 40, 367, 242, 411, 282, 0, 0
		
	INVOKE LoadBitmap, hInstance, 1111
	mov Thief_right_s_img, eax
	INVOKE LoadBitmap, hInstance, 2222
	mov Thief_left_s_img, eax
	INVOKE LoadBitmap, hInstance, 3333
	mov Thief_right_r_img, eax
	INVOKE LoadBitmap, hInstance, 4444
	mov Thief_left_r_img, eax
	
	ret

InitItemList endp