#include"windows.h"
#include"stdio.h"
#include<string.h>
typedef char charMax[MAX_PATH];
void main(){
	charMax szWinPath;
	charMax szPath;
	charMax szFileName;
	char* pst = NULL;
	GetModuleFileName(NULL,szFileName,sizeof(szFileName));
	GetWindowsDirectory(szWinPath,sizeof(szWinPath));//获取windows文件夹的路径
	GetSystemDirectory(szPath,sizeof(szPath));//获取system32的路径

	printf("filename->%s\n",szFileName);
	printf("winpath->%s\n",szPath);
	printf("systempath->%s\n",szWinPath);
	pst = strrchr(szFileName,'\\');
	//pst++; 不需要要++正好需要这个'/'
	//printf("%s\n",pst);//估计是读到'\0'结束

	strcat(szPath,pst);
	strcat(szWinPath,pst);

	printf("szPath->%s\n",szWinPath);
	printf("szPath->%s\n",szPath);
	printf("szFileName->%s\n",szFileName);

	CopyFile(szFileName,szWinPath,true);
	CopyFile(szFileName,szPath,true);
}
