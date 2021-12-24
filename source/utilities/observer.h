/**
 * @file observer.h
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <vector>

class Subject;

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void update(Subject&) = 0;
};

class Subject
{
public:
	virtual ~Subject() = default;
	void attach(Observer& o)
	{
		m_observers.push_back(&o);
	}

	void detach(Observer& o)
	{
		m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), &o));
	}

	void notify()
	{
		for (auto* o : m_observers)
		{
			o->update(*this);
		}
	}

private:
	std::vector<Observer*> m_observers;
};

#endif // OBSERVER_H_
