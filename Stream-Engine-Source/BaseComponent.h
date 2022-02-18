#pragma once
#include <memory>

namespace StreamEngine
{
	class GameObject;
	
	class BaseComponent
	{
	public:
		explicit BaseComponent(std::weak_ptr<GameObject> pOwningGameObject);
		virtual ~BaseComponent() = default;

#pragma warning (push)
#pragma warning (disable:4100)
		virtual void Update(float deltaTime) {};
		virtual void FixedUpdate(float deltaTime) {};
		virtual void LateUpdate(float deltaTime) {};
#pragma warning (pop)
		virtual void Render() const {};
		
		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) noexcept = delete;
		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(BaseComponent&&) noexcept = delete;
	protected:
		std::weak_ptr<GameObject> m_pOwningGameObject;
	};
}
