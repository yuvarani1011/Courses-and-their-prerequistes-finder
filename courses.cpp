#include<iostream>
#include<cstdlib>
#include<list>
#include<vector>
#include<queue>
#include<stack>
#include<cstring>
using namespace std;
class graph
{
    public:
        int NUM_VERTICES;
        string ar[10];
        list<string> *adj;
        list<int> *adj1;
        graph(int v)
        {
            this->NUM_VERTICES=v;
            adj=new list<string>[NUM_VERTICES];
            adj1=new list<int>[NUM_VERTICES];
        }
        
        void get_courses(int a,string b)
        {
            adj[a].push_back(b);
            ar[a]=b;
        }
        void addedge(string a,string b)
        {
            list<string>::iterator it;
            for(int i=0;i<NUM_VERTICES;i++)
            {
                for(it=adj[i].begin();it!=adj[i].end();it++)
                {
                    string f=*it;
                    if((f.compare(a))==0)
                    {
                        adj[i].push_back(b);
                        for(int g=0;g<NUM_VERTICES;g++)
                        {
                            string y=ar[g];
                            if((y.compare(b))==0)
                            {
                                adj1[i].push_back(g);
                                break;
                            }
                        }
                    }
                    else
                        break;
                }
            }
        }
        void print()
        {
            vector<int> indegree(NUM_VERTICES,0);
            for(int u=0;u<NUM_VERTICES;u++)
            {
                list<int>::iterator itr;
                for(itr=adj1[u].begin();itr != adj1[u].end();++itr)
                {
                    //cout<<*itr<<endl;
                    ++indegree[*itr];
                }
            }
        
            /* for(int i=0;i<indegree.size();i++)
            {
            cout<<indegree[i];
            }*/
            
            queue<int> q;
            for(int i=0;i<NUM_VERTICES;i++)
            if(indegree[i]==0)
            q.push(i);
            int counter=0;
            
            vector<int> toporder;
            while(!q.empty())
            {
                int u=q.front();
                // cout<<u<<"  ";
                q.pop();
                toporder.push_back(u);
                
                list<int>::iterator itr;
                for(itr=adj1[u].begin();itr!=adj1[u].end();itr++)
                {
                    if(--indegree[*itr]==0)
                        q.push(*itr);
                }
                counter++;
            }
            //for(int i=0;i<10;i++)
            //cout<<toporder[i]<<" ";
            for(int i=0;i<toporder.size();i++)
            {
                list<string>::iterator it;
                int temp=toporder[i];
                for(it=adj[temp].begin();it!=adj[i].end();++it)
                {
                    cout<<*it<<"  ";
                    break;
                }
            }
            cout<<endl;
            /*list<string>::iterator it;
            for(int i=0;i<NUM_VERTICES;i++)
            {
            cout<<i<<endl;
            for(it=adj[i].begin();it!=adj[i].end();++it)
            {
            
            cout<<*it<<endl;
            }
            }*/
        }
        void prereq(string a)
        {
            string pre;int j=0,s=0;
            cout<<"Prerequisite :";
            list<string>::iterator it;
            for(int i=0;i<NUM_VERTICES;i++)
            {
                j=i;
                for(it=adj[i].begin();it!=adj[i].end();++it)
                {
                    if(i==j)
                    {
                        pre=*it;++it;
                        if(it==adj[i].end())
                            break;
                    }
                    if(*it==a)
                    {
                        cout<<pre<<" \t";
                        break;
                    }
                    else
                    {
                        j=j+1;
                    }
                }
            }
            cout<<endl;
        }
        
        
        void course()
        {
            string cou;int s=0;
            cout<<"\nEnter the prerequisite course ";
            cin>>cou;
            cout<<"\nYou could take up "<<endl;
            list<string>::iterator it;
            for(int i=0;i<NUM_VERTICES;i++)
            {
                for(it=adj[i].begin();it!=adj[i].end();++it)
                {
                    if(s==0)
                    {
                        string tmp=*it;
                        if((tmp.compare(cou))==0)
                            ++it;
                        s=1;
                    }
                    if(s==1)
                    {
                        string temp=*it;
                        cout<<temp<<endl;
                    }
                }
                if(s==1)
                    break;
                else 
                    s=0;
            }
        }

};


int main()
{
    string a,b;
    int n,x;
    cout<<"\nEnter no. of courses ";
    cin>>n;
    graph g(n);
    cout<<"--OPTIONS--\n1.Insert\n2.Addedge\n3.Course->Prerequisite\n4.Prerequisite->Course\n5.Print\n";
    do
    {
        cout<<"\nEnter choice:";
        cin>>x;
        switch(x)
        {
            case 1:
                {
                    for(int i=0;i<n;i++)
                    {
                        cout<<"Enter a value:";
                        cin>>a;
                        g.get_courses(i,a);
                    }
                    break;
                }
            case 2:
            {
                cout<<"Enter course and its next course:";
                cin>>a>>b;
                g.addedge(a,b);
                break;
            }
    
            case 3:
            {
                cout<<"enter a course:";
                cin>>a;
                g.prereq(a);
                break;
            }
            case 4:
            {
                g.course();
                break;
            }
            case 5:
            {
                g.print();
                break;
            }
            default:
            {
                exit(0);
                break;
            }
        }
    }while(1);
    return 0;
}
