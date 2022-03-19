#pragma once

namespace StreamEngine
{
	class GameObject;

	class Observer
	{
	public:
		enum class Event
		{
			Die = 0
		};

		virtual ~Observer() = default;
		virtual void Notify(const StreamEngine::GameObject& gameObject, Event event) = 0;
	};
}
