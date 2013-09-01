#pragma once
#include <vector>
#include "PerceptronLayer.h"
#include "FeatureSet.h"
#include <atomic>

using namespace std;
using namespace ann;
namespace ann{
template<typename T> class network
{
	//friend void PerceptronLayer<T>::setReadyFlag();
public:
	network(PerceptronLayer<T>& _initl) : _start(_initl)
	{
		//_count=0;
		//_currReady=0;
	}
	void addEndPoint(PerceptronLayer<T>& _endl)
	{
		//_end.push_back(_endl);
		//_endl.setNetwork((void*) this);
		_end.push_back(_endl.data());
	}
	void makeReady()
	{
		for(int i(0);i<_end.size();i++)
		{
			while (true)
			{
				if (_end.at(i)->isReady())
				{
					break;
				}
				this_thread::yield();
			}
		}

	}
	/**
	the network feed function
	*/
	void feed(FeatureSet<T> _inp)
	{
		//this feed is developed to support multiple layers
		//_start._feed(_inp);
		_start._feed(_inp);
	}
	void feed(vector<T> _inp,size_t _ch=1)
	{
		FeatureSet<T> tmp(_inp,_ch);
		cout<<tmp.getChannel()<<"\n";
		_start._feed(tmp);
	}
private:
	PerceptronLayer<T>& _start;
	vector<PerceptronLayer<T>*> _end;
	//map<PerceptronLayer<T>&,FeatureSet<T> > _out;
};
}
