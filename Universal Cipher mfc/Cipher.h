#ifndef CIPHER
#define CIPHER true
#define DECIPHER false
#define NUMBER 1
#define SYMBOL 2
#define EXPANDED 3
#define OK 0
#define ERRORKEY 1
#define ERRORSHUFFLE 2
#define ERRORTYPE 3
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <ctime>
#include "Universal Cipher mfcDlg.h"

using namespace std;

class Cipher
{
	class _Cipher
	{
		int a[10];
		int summ(int x)
		{
			int s;
			while (x>9)
			{
				s=0;
				while (x)
				{
					s+=x%10;
					x/=10;
				}
				x=s;
			}
			return x;
		}

		int decipher(int x)
		{
			int s,j;
			bool flag=false;
			for(j=0;j<10;++j)
				a[j]^=a[j];
			j=x;
			while (x)
			{
				++a[x%10];
				x/=10;
			}
			s=summ(j);
			for (j=1;j<10;++j)
			{
				if (s<10)
				{
					if(!a[s])
					{
						flag=true;
						break;
					}
					else
						s*=a[s]+1;
				}
				s=summ(s);
			}
			return flag?s:0;
		}

		bool decipher(int x,int z)
		{
			int s,j,z1;
			bool flag=false;
			for(j=0;j<10;++j)
				a[j]^=a[j];
			j=x;
			while (x)
			{
				z1=x%10;
				if (z1==z && z)
					return false;
				++a[z1];
				x/=10;
			}
			s=summ(j);
			for (j=1;j<10;++j)
			{
				if (s<10)
				{
					if(!a[s])
					{
						flag=true;
						break;
					}
					else
						s*=a[s]+1;
				}
				s=summ(s);
			}
			return flag?(s==z):(!z);
		}

		int cipher(int x)
		{
			int z=0;
			while (z<10000 || z>99999)
			{
				z=rand()%100000;
				while (!decipher(z,x))
					z=rand()%100000;
			}
			return z;
		}

		void do_key(const string &key,string &key1)
		{
			int i;
			key1=key[0];
			for (i=1;i<29;i+=2)
				if (key[i]=='0' || (key[i]=='1' && key[i+1]=='0'))
				{
					key1+=key[i];
					key1+=key[i+1];
				}
			int len=key1.length();
			if (len<=20)
			{
				bool flag[10];
				for (i=0;i<10;++i)
					flag[i]^=flag[i];
				for (i=2;i<len;i+=2)
					flag[key1[i]-'0']=true;
				for (i=0;i<10;++i)
					if (!flag[i])
					{
						key1+=i?'0':'1';
						key1+=i+'0';
						break;
					}
			}
		}

		void shuffle(string &s,const string &key)
		{
			int i,j,k,x,y,len=s.length();
			string key1;
			do_key(key,key1);
			for (i=0;i<len;)
			{
				if (i+9>len)
					break;
				if (s[i+10]!=':' && i+15<len)
				{
					for (j=0;j<key[0]-'0';++j)
						for (k=1;k<29;k+=4)
						{
							if (j&1)
							{
								x=(key[k]-'0')*10+key[k+1]-'0';
								y=(key[k+2]-'0')*10+key[k+3]-'0';
							}
							else
							{
								x=key[k]+key[k+1]-'0'-'0';
								y=key[k+2]+key[k+3]-'0'-'0';
							}
							--x;
							--y;
							if (x-y)
							{
								s[i+x]^=s[i+y];
								s[i+y]^=s[i+x];
								s[i+x]^=s[i+y];
							}
						}
					i+=16;
				}
				else
				{
					for (j=0;j<key1[0]-'0';++j)
						for (k=1;k<21;k+=4)
						{
							if (j&1)
							{
								x=(key1[k]-'0')*10+key1[k+1]-'0';
								y=(key1[k+2]-'0')*10+key1[k+3]-'0';
							}
							else
							{
								x=key1[k]+key1[k+1]-'0'-'0';
								y=key1[k+2]+key1[k+3]-'0'-'0';
							}
							--x;
							--y;
							if (x-y)
							{
								s[i+x]^=s[i+y];
								s[i+y]^=s[i+x];
								s[i+x]^=s[i+y];
							}
						}
					i+=11;
				}
			}
		}

		void deshuffle(string &s,const string &key)
		{
			int i,j,k,x,y,len=s.length();
			string key1;
			do_key(key,key1);
			for (i=0;i<len;)
			{
				if (i+9>len)
					break;
				if (s[i+10]!=':' && i+15<len)
				{
					for (j=key[0]-'0'-1;j>=0;--j)
						for (k=25;k>0;k-=4)
						{
							if (j&1)
							{
								x=(key[k]-'0')*10+key[k+1]-'0';
								y=(key[k+2]-'0')*10+key[k+3]-'0';
							}
							else
							{
								x=key[k]+key[k+1]-'0'-'0';
								y=key[k+2]+key[k+3]-'0'-'0';
							}
							--x;
							--y;
							if (x-y)
							{
								s[i+x]^=s[i+y];
								s[i+y]^=s[i+x];
								s[i+x]^=s[i+y];
							}
						}
					i+=16;
				}
				else
				{
					for (j=key1[0]-'0'-1;j>=0;--j)
						for (k=17;k>0;k-=4)
						{
							if (j&1)
							{
								x=(key1[k]-'0')*10+key1[k+1]-'0';
								y=(key1[k+2]-'0')*10+key1[k+3]-'0';
							}
							else
							{
								x=key1[k]+key1[k+1]-'0'-'0';
								y=key1[k+2]+key1[k+3]-'0'-'0';
							}
							--x;
							--y;
							if (x-y)
							{
								s[i+x]^=s[i+y];
								s[i+y]^=s[i+x];
								s[i+x]^=s[i+y];
							}
						}
					i+=11;
				}
			}
		}

		void shufflenum(string &s,const string &key)
		{
			int i,j,k,x,y,len=s.length();
			for (i=0;i<len;i+=15)
			{
				if (i+15<len)
					for (j=0;j<key[0]-'0';++j)
						for (k=1;k<29;k+=4)
						{
							if (j&1)
							{
								x=(key[k]-'0')*10+key[k+1]-'0';
								y=(key[k+2]-'0')*10+key[k+3]-'0';
							}
							else
							{
								x=key[k]+key[k+1]-'0'-'0';
								y=key[k+2]+key[k+3]-'0'-'0';
							}
							if (x-y)
							{
								s[i+x-1]^=s[i+y-1];
								s[i+y-1]^=s[i+x-1];
								s[i+x-1]^=s[i+y-1];
							}
						}
			}
		}

		void deshufflenum(string &s,const string &key)
		{
			int i,j,k,x,y,len=s.length();
			for (i=0;i<len;i+=15)
			{
				if (i+15<len)
					for (j=key[0]-'0'-1;j>=0;--j)
						for (k=25;k>0;k-=4)
						{
							if (j&1)
							{
								x=(key[k]-'0')*10+key[k+1]-'0';
								y=(key[k+2]-'0')*10+key[k+3]-'0';
							}
							else
							{
								x=key[k]+key[k+1]-'0'-'0';
								y=key[k+2]+key[k+3]-'0'-'0';
							}
							if (x-y)
							{
								s[i+x-1]^=s[i+y-1];
								s[i+y-1]^=s[i+x-1];
								s[i+x-1]^=s[i+y-1];
							}
						}
			}
		}

		void shuffletxt(string &s,const string &key)
		{
			int i,j,k,x,y,len=s.length();
			string key1;
			do_key(key,key1);
			for (i=0;i<len;i+=10)
			{
		//		if (i+10<len)
				for (j=0;j<key1[0]-'0';++j)
					for (k=1;k<21;k+=4)
					{
						if (j&1)
						{
							x=(key1[k]-'0')*10+key1[k+1]-'0';
							y=(key1[k+2]-'0')*10+key1[k+3]-'0';
						}
						else
						{
							x=key1[k]+key1[k+1]-'0'-'0';
							y=key1[k+2]+key1[k+3]-'0'-'0';
						}
						if (x-y)
						{
							s[i+x-1]^=s[i+y-1];
							s[i+y-1]^=s[i+x-1];
							s[i+x-1]^=s[i+y-1];
						}
					}
			}
		}

		void deshuffletxt(string &s,const string &key)
		{
			int i,j,k,x,y,len=s.length();
			string key1;
			do_key(key,key1);
			for (i=0;i<len;i+=10)
			{
		//		if (i+10<len)
				for (j=key1[0]-'0'-1;j>=0;--j)
					for (k=17;k>0;k-=4)
					{
						if (j&1)
						{
							x=(key1[k]-'0')*10+key1[k+1]-'0';
							y=(key1[k+2]-'0')*10+key1[k+3]-'0';
						}
						else
						{
							x=key1[k]+key1[k+1]-'0'-'0';
							y=key1[k+2]+key1[k+3]-'0'-'0';
						}
						if (x-y)
						{
							s[i+x-1]^=s[i+y-1];
							s[i+y-1]^=s[i+x-1];
							s[i+x-1]^=s[i+y-1];
						}
					}
			}
		}

	public:
		void rand_key(string &key)
		{
			bool flag[16];
			for (int i=0;i<16;++i)
				flag[i]^=flag[i];
			int x;
			key="";
			key+=rand()%9+'1';
			for (int i=0;i<14;++i)
			{
				x=rand()%15+1;
				while(flag[x])
					x=rand()%15+1;
				flag[x]=true;
				key+=x/10+'0';
				key+=x%10+'0';
			}
		}

		void cipherstr(const string &s,string &s1,string &key,bool _rand=true,bool _useKey=true)
		{
			int x,y,len=s.length();
			if (_rand)
				rand_key(key);
			s1="";
			for (int i=0;i<len;++i)
			{
				y=s[i];
				do
				{
					x=cipher(y%10);
					y/=10;
					while (x)
					{
						s1+=(x%10+'0');
						x/=10;
					}
				} while (y);
				if (i!=len-1)
					s1+=':';
			}
			if (_useKey)
				shuffle(s1,key);
		}

		void decipherstr(string &s,string &s1,const string &key,bool _useKey=true)
		{
			s1="";
			if (_useKey)
				deshuffle(s,key);
			int x,y,a,j,len=s.length();
			for (int i=0;i<len;++i)
			{
				j=i;
				a=1;
				y^=y;
				while(s[i]!=':' && i!=len)
				{
					x^=x;
					while(i-j!=5)
					{
						x*=10;
						x+=s[i++]-'0';
					}
					j+=5;
					y+=decipher(x)*a;
					a*=10;
				}
				s1+=y;
			}
		}

		void ciphernum(const string &s,string &s1,string &key,bool _rand=true,bool _useKey=true)
		{
			int x,len=s.length();
			if (_rand)
				rand_key(key);
			s1="";
			for (int i=0;i<len;++i)
			{
				x=cipher(s[i]-'0');
				for(;x;x/=10)
					s1+=(x%10+'0');
			}
			if (_useKey)
				shufflenum(s1,key);
		}

		void deciphernum(string &s,string &s1,const string &key,bool _useKey=true)
		{
			s1="";
			if (_useKey)
				deshufflenum(s,key);
			int x,y,j,len=s.length();
			for (int i=0;i<len;i+=5)
			{
				x^=x;
				for (j=0;j<5;++j)
				{
					x*=10;
					x+=s[i+j]-'0';
				}
				y=decipher(x);
				s1+=y+'0';
			}
		}

		void ciphertxt(const string &s,string &s1,string &key,bool _rand=true,bool _useKey=true)
		{
			int x,y,len=s.length();
			const int shift=22;
			if (_rand)
				rand_key(key);
			s1="";
			for (int i=0;i<len;++i)
				if (s[i]==10)
				{
					y=36-shift;
					x=cipher(y%10);
					for(;x;x/=10)
						s1+=(x%10+'0');
					x=cipher(y/10);
					for(;x;x/=10)
						s1+=(x%10+'0');
				}
				else
					if (s[i]<96)
					{
						y=s[i]-shift;
						x=cipher(y%10);
						for(;x;x/=10)
							s1+=(x%10+'0');
						x=cipher(y/10);
						for(;x;x/=10)
							s1+=(x%10+'0');
					}
					else
					{
						y=s[i]-shift-1;
						x=cipher(y%10);
						for(;x;x/=10)
							s1+=(x%10+'0');
						x=cipher(y/10);
						for(;x;x/=10)
							s1+=(x%10+'0');
					}
			if (_useKey)
				shuffletxt(s1,key);
		}

		void deciphertxt(string &s,string &s1,const string &key,bool _useKey=true)
		{
			const int shift=22;
			s1="";
			if (_useKey)
				deshuffletxt(s,key);
			int x,y,z,j,len=s.length();
			for (int i=0;i<len;i+=10)
			{
				x^=x;
				for (j=0;j<5;++j)
				{
					x*=10;
					x+=s[i+j]-'0';
				}
				y=decipher(x);
				x^=x;
				for (j=5;j<10;++j)
				{
					x*=10;
					x+=s[i+j]-'0';
				}
				z=decipher(x)*10+y;
				if (z==14)
					z=-12;
				if (z>73)
					++z;
				s1+=z+shift;
			}
		}

		void safeCipherstr(const string &s,string &s1)
		{
			cipherstr(s,s1,s1,false,false);
		}

		void safeCiphernum(const string &s,string &s1)
		{
		}

		void safeCiphertxt(const string &s,string &s1)
		{
		}

		void safeDecipherstr(string &s,string &s1)
		{
		}

		void safeDeciphernum(string &s,string &s1)
		{
		}

		void safeDeciphertxt(string &s,string &s1)
		{
		}

		bool checkKey(const string &_key)
		{
			if (_key.length()!=29)
				return false;
			if (_key[0]=='0')
				return false;
			bool flag[16];
			for (int i=0;i<16;++i)
				flag[i]^=flag[i];
			int x;
			for (int i=1;i<29;i+=2)
			{
				x=(_key[i]-'0')*10+_key[i+1]-'0';
				if (flag[x])
					return false;
				else
					flag[x]=true;
			}
			return true;
		}

		bool checkCipherType(const string &_initialStr,int _cipherType)
		{
			int len=_initialStr.length();
			switch (_cipherType)
			{
			case NUMBER:
				for (int i=0;i<len;i++)
					if (_initialStr[i]<'0' || _initialStr[i]>'9')
						return false;
				break;
			case SYMBOL:
				for (int i=0;i<len;i++)
					if ((_initialStr[i]<32 || _initialStr[i]==96 || _initialStr[i]>122 || _initialStr[i]==36) && _initialStr[i]!=10)
						return false;
				break;
			}
			return true;
		}

		bool checkDecipherType(const string &_initialStr,int cipherType)
		{
			int len=_initialStr.length();
			if (!len)
				return true;
			switch (cipherType)
			{
			case NUMBER:
				if (len%5)
					return false;
				for (int i=0;i<len;i++)
					if (_initialStr[i]<'0' || _initialStr[i]>'9')
						return false;
				break;
			case SYMBOL:
				if (len%10)
					return false;
				for (int i=0;i<len;i++)
					if (_initialStr[i]<'0' || _initialStr[i]>'9')
						return false;
				break;
			case EXPANDED:
				int lastColon=0,calculator=0;
				for (int i=0;i<len;i++)
					if (_initialStr[i]<'0' || _initialStr[i]>'9')
						if (_initialStr[i]==':' && (i-lastColon==10 || i-lastColon==15))
						{
							lastColon=i+1;
							calculator^=calculator;
						}
						else
							return false;
					else
						++calculator;
				if (len>15 && !lastColon)
					return false;
				if (calculator!=10 && calculator!=15)
					return false;
				break;
			}
			return true;
		}
	} _c;
public:
	Cipher()
	{
		srand((unsigned)time(NULL));
	}

	int cipher(const string &_initialStr,string &_finalStr,
		string &_key,int _cipherType,bool _rand=true,bool _useKey=true)
	{
		int checkResult=check(_initialStr,_key,_cipherType,CIPHER,_rand,_useKey);
		if (checkResult!=OK)
			return checkResult;
		switch(_cipherType)
		{
		case NUMBER:
			_c.ciphernum(_initialStr,_finalStr,_key,_rand,_useKey);
			break;
		case SYMBOL:
			_c.ciphertxt(_initialStr,_finalStr,_key,_rand,_useKey);
			break;
		case EXPANDED:
			_c.cipherstr(_initialStr,_finalStr,_key,_rand,_useKey);
			break;
		default:
			return ERRORTYPE;
		}
		return OK;
	}

	int safeCipher(const string &_initialStr,string &_finalStr,int _cipherType)
	{
		int checkResult=check(_initialStr,_finalStr,_cipherType,CIPHER,true,true,true);
		switch(_cipherType)
		{
		case NUMBER:
			_c.safeCiphernum(_initialStr,_finalStr);
			break;
		case SYMBOL:
			_c.safeCiphertxt(_initialStr,_finalStr);
			break;
		case EXPANDED:
			_c.safeCipherstr(_initialStr,_finalStr);
			break;
		default:
			return ERRORTYPE;
		}
		return OK;
	}

	int decipher(string &_initialStr,string &_finalStr,
		string &_key,int _cipherType,bool _useKey=true)
	{
		int checkResult=check(_initialStr,_key,_cipherType,DECIPHER,true,_useKey);
		if (checkResult!=OK)
			return checkResult;
		switch(_cipherType)
		{
		case NUMBER:
			_c.deciphernum(_initialStr,_finalStr,_key,_useKey);
			break;
		case SYMBOL:
			_c.deciphertxt(_initialStr,_finalStr,_key,_useKey);
			break;
		case EXPANDED:
			_c.decipherstr(_initialStr,_finalStr,_key,_useKey);
			break;
		default:
			return ERRORTYPE;
		}
		return OK;
	}

	int safeDecipher(string &_initialStr,string &_finalStr,int _cipherType)
	{
		int checkResult=check(_initialStr,_finalStr,_cipherType,DECIPHER,true,true,true);
		if (checkResult!=OK)
			return checkResult;
		if (restoreInitialStr(_initialStr,_cipherType))
			switch(_cipherType)
			{
			case NUMBER:
				_c.safeDeciphernum(_initialStr,_finalStr);
				break;
			case SYMBOL:
				_c.safeDeciphertxt(_initialStr,_finalStr);
				break;
			case EXPANDED:
				_c.safeDecipherstr(_initialStr,_finalStr);
				break;
			default:
				return ERRORTYPE;
			}
		else
			return ERRORTYPE;
		return OK;
	}

	int check(const string &_initialStr,const string &_key,
		int _cipherType,bool _command,bool _rand=true,bool _useKey=true,bool _safeCipher=false)
	{
		if (_command==CIPHER)
		{
			if (!_c.checkKey(_key) && !_rand && _useKey && !_safeCipher)
				return ERRORKEY;
			if (!_c.checkCipherType(_initialStr,_cipherType))
				return ERRORTYPE;
		}
		else
			if (!_safeCipher)
			{
				if (!_c.checkKey(_key) && _useKey)
					return ERRORKEY;
				if (!_c.checkDecipherType(_initialStr,_cipherType))
					return ERRORTYPE;
			}
		return OK;
	}

	bool restoreKey(string &_key)
	{
		if (_c.checkKey(_key))
			return true;
		if (_key.length()==28 && _key[0]=='0')
		{
			_key=(char)(rand()%9+'1')+_key;
			return false;
		}
		int posNum[16],posStr[29];
		for (int i=0;i<16;i++)
			posNum[i]=-1;
		for (int i=0;i<29;i++)
			posStr[i]=-1;
		for (int i=1;i<16;i++)
		{
			string tmp;
			tmp+=i/10+'0';
			tmp+=i%10+'0';
			int x;
			x=_key.rfind(tmp);
			if (x!=-1)
			{
				posNum[i]=x;
				posStr[x]=i;
			}
		}
		int odd=0,even=0;
		for (int i=1;i<16;i++)
			if (posNum[i]!=-1)
				if (posNum[i]&1)
					++odd;
				else
					++even;
		int maxPosDisplacement=0;
		if (_key.length()==28)
		{
			if (even==14)
			{
				_key=(char)(rand()%9+'1')+_key;
				if (!_c.checkKey(_key))
					_key="";
				return false;
			}
			else
			{
				string restoredKey;
				restoredKey.resize(29);
				restoredKey[0]=_key[0];
				for (int i=1;i<29;i++)
					restoredKey[i]='?';
				for (int i=6;i<10;i++)
					if (posNum[i]!=-1)
						if (posNum[i]&1)
						{
							if (maxPosDisplacement<=posNum[i])
								maxPosDisplacement=posNum[i]+2;
							restoredKey[posNum[i]]='0';
							restoredKey[posNum[i]+1]=i+'0';
						}
						else
						{
							restoredKey[posNum[i]+1]='0';
							restoredKey[posNum[i]+2]=i+'0';
						}
				for (int i=2;i<6;i++)
					if (posNum[i]!=-1 && posNum[i+10]!=-1)
					{
						if (posNum[i]&1)
						{
							if (maxPosDisplacement<=posNum[i])
								maxPosDisplacement=posNum[i]+2;
							restoredKey[posNum[i]]='0';
							restoredKey[posNum[i]+1]=i+'0';
						}
						else
						{
							restoredKey[posNum[i]+1]='0';
							restoredKey[posNum[i]+2]=i+'0';
						}
						if (posNum[i+10]&1)
						{
							if (maxPosDisplacement<=posNum[i])
								maxPosDisplacement=posNum[i]+2;
							restoredKey[posNum[i+10]]='1';
							restoredKey[posNum[i+10]+1]=i%10+'0';
						}
						else
						{
							restoredKey[posNum[i+10]+1]='1';
							restoredKey[posNum[i+10]+2]=i%10+'0';
						}
					}
				for (unsigned int i=0;i<_key.length();)
				{
					unsigned int j;
					while (_key[i]==restoredKey[i])
						++i;
					for (j=i;j<29 && restoredKey[j]=='?';j++);
					if (_key[j-1]==restoredKey[j])
					{
						while (posStr[i]!=-1 && i<j)
						{
							if (i==posNum[posStr[i]] && i&1 && !(i+1==posNum[posStr[i+1]] && !(i+2==posNum[posStr[i+2]])))
							{
								restoredKey[i]=_key[i];
								restoredKey[i+1]=_key[i+1];
								i+=2;
							}
							else
								break;
						}
						for (int k=i+2;k<29;k++)
							restoredKey[k]=_key[k-1];
						bool flag[16];
						for (int k=0;k<16;k++)
							flag[k]^=flag[k];
						for (int k=1;k<29;k+=2)
							if (restoredKey[k]!='?')
							{
								flag[(restoredKey[k]-'0')*10+restoredKey[k+1]-'0']=true;
							}
						if (_key[i]!='0' && _key[i]!='1')
						{
							int k;
							for (k=2;k<16;k++)
								if (!flag[k] && k!=10 && k!=11)
									break;
							restoredKey[i]=k/10+'0';
							restoredKey[i+1]=k%10+'0';
							_key=restoredKey;
							return true;
						}
						else
						{
							if (_key[i]=='1')
							{
								int k=0;
								int last;
								for (int z=10;z<16;z++)
									if (!flag[z])
									{
										k++;
										last=z;
									}
								if (k==2 || last==10)
								{
									_key=restoredKey;
									_key[i]='1';
									_key[i+1]=last%10+'0';
									return false;
								}
								if (k==1)
								{
									_key=restoredKey;
									_key[i]='1';
									_key[i+1]=last%10+'0';
									return true;
								}
								_key=restoredKey;
								_key[i]='0';
								_key[i+1]='1';
								return true;
							}
							else
							{
								int k=0,last;
								for (int z=1;z<10;z++)
									if (!flag[z])
									{
										k++;
										last=z;
									}
								if (k==2 || last==1)
								{
									_key=restoredKey;
									_key[i]='0';
									_key[i+1]=last%10+'0';
									return false;
								}
								if (k==1)
								{
									_key=restoredKey;
									_key[i]='0';
									_key[i+1]=last%10+'0';
									return true;
								}
								_key=restoredKey;
								_key[i]='1';
								_key[i+1]='0';
								return true;
							}
						}
						break;
					}
					else
					{
						for (unsigned int k=i;k<j;k++)
							restoredKey[k]=_key[k];
						i=j;
					}
				}
				return true;
			}
		}
		return false;
	}

	bool restoreInitialStr(string &_initialStr,int _cipherType)
	{
		return true;
	}
};

#endif CIPHER