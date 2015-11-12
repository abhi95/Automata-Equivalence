#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <stack>
#include "UnionFind.cpp"

using namespace std;

typedef struct adj 				//Structure of adjacency list
{
	int next;
	char ch;
}Node;

typedef struct stData 				//Structure of adjacency list
{
	int p;
	int q;
}sNode;

vector< vector< Node > > delta1,delta2;
int nextState(int cur,char input,int noStates1,int noStates2)
{
	int i=0;
	if(cur<noStates1)
	{	
		for(i=0;i<delta1[cur].size();i++)
		{
			if(delta1[cur][i].ch==input)
				return delta1[cur][i].next;
		}
	}
	else
	{
		for(i=0;i<delta2[cur].size();i++)
		{
			if(delta2[cur-noStates1][i].ch==input)
				return delta2[cur-noStates1][i].next+noStates1;
		}
	}
	return -1;
}

int main()
{
	int noStates1,noStates2,noChar1,noChar2,noEdges1,noEdges2,i,x,z,temp1,temp2,j;
	stack<sNode> st;
	sNode stackNode,tSN;
	char alpha1[100],alpha2[100],y;
	Node temp;
	

//===================Automata 1 Input======================
	printf("Enter the number of states in first automata\n");
	scanf("%d",&noStates1);
	delta1.resize(noStates1);
	printf("Enter the number of characters and each characters \n");
	scanf("%d",&noChar1);
	for (i = 0; i < noChar1;i++)
		scanf(" %c",&alpha1[i]);
	printf("Enter number of edges\n");
	scanf("%d",&noEdges1);
	printf("Enter the delta function state1 character state2 let 0 be the starting state\n");
	temp1=noEdges1;
	while(temp1--)
	{
		scanf("%d",&x);
		scanf(" %c",&y);
		scanf("%d",&z);
		temp.next=z;
		temp.ch=y;
		delta1[x].push_back(temp);
	}

	// for(i=0;i<delta1.size();i++)
	// {
	// 	printf("%d ",i);
	// 	for(j=0;j<delta1[i].size();j++)
	// 		printf("%c %d ",delta1[i][j].ch,delta1[i][j].next);
	// 	printf("\n");
	// }

//=================Automata 2 Input========================
	printf("Enter the number of states in second automata\n");
	scanf("%d",&noStates2);
	delta2.resize(noStates2);
	printf("Enter the number of characters and each characters \n");
	scanf("%d",&noChar2);
	for (i = 0; i < noChar2;i++)
		scanf(" %c",&alpha2[i]);
	printf("Enter number of edges\n");
	scanf("%d",&noEdges2);
	printf("Enter the delta function state1 character state 2 let 0 be the starting state\n");
	temp2=noEdges2;
	while(temp2--)
	{
		scanf("%d",&x);
		scanf(" %c",&y);
		scanf("%d",&z);
		temp.next=z;
		temp.ch=y;
		delta2[x].push_back(temp);
	}

//============Hopcraft Algorithm=============================
	
	int pResult,qResult,pSet,qSet;
	DisjointSets s(noStates1+noStates2);
	stackNode.p=0;
	stackNode.q=noStates1;
	st.push(stackNode);
	while(!st.empty())
	{
		stackNode=st.top();
		st.pop();
		printf("popped p is %d popped q is %d\n",stackNode.p,stackNode.q);
		printf("\n");


///////////////   Languages being different is not taken care 
		// for(i=0;i<noChar2+noChar1;i++)
		// {
		// 	if(i<noChar1)
		// 	{
		// 		pResult=nextState(stackNode.p,alpha1[i],noStates1,noStates2);
		// 		qResult=nextState(stackNode.q,alpha1[i],noStates1,noStates2);
		// 	}
		// 	else
		// 	{
		// 		pResult=nextState(stackNode.p,alpha2[i-noChar1],noStates1,noStates2);
		// 		qResult=nextState(stackNode.q,alpha2[i-noChar1],noStates1,noStates2);
		// 	}
		// 	pSet=s.FindSet(pResult);
		// 	qSet=s.FindSet(qResult);
		// 	if(pSet!=qSet)
		// 	{
		// 		s.Union(pSet,qSet);
		// 		stackNode.p=pSet;
		// 		stackNode.q=qSet;
		// 		st.push(stackNode);
		// 	}
		// }
		for(i=0;i<noChar1;i++)
		{
			pResult=nextState(stackNode.p,alpha1[i],noStates1,noStates2);
			qResult=nextState(stackNode.q,alpha1[i],noStates1,noStates2);
			if(pResult==-1 && qResult==-1)
				continue;
			printf("pResult is %d  qResult is %d character is %d\n",pResult,qResult,alpha1[i]);	
			pSet=s.FindSet(pResult);
			qSet=s.FindSet(qResult);
			printf("pset is %d qset is %d\n",pSet,qSet);
			if(pSet!=qSet)
			{
				s.Union(pSet,qSet);
				tSN.p=pSet;
				tSN.q=qSet;
				printf("Pushed p is %d Pushed q is %d\n",pSet,qSet);
				st.push(tSN);
			}
		}
		printf("The set Identities are\n");
		printElementSets(s);
		printf("\n\n\n");
		
	}



	printElementSets(s);

	
	return 0;
}