#pragma once
#include "Observer.h"
#include <memory>
#include <vector>

namespace StreamEngine
{
	class Subject
	{
	public:
		void AddObserver(std::shared_ptr<Observer> observer)
		{
			
		}
		void RemoveObserver(std::shared_ptr<Observer> observer)
		{
			
		}

	protected:
		void Notify(const GameObject& actor, Observer::Event event)
		{
			for (auto pObserver : m_pObservers)
			{
				pObserver->Notify(actor, event);
			}
		}

	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers{};
	};
}
