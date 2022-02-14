#pragma once
#include <map>

#include "Transform.h"
#include <vector>
#include <string>

namespace StreamEngine
{
	class BaseComponent;
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		//Update handling
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void LateUpdate(float deltaTime);

		//Components handling
		void AddComponent(std::shared_ptr<BaseComponent> pComponent);
		template <typename T>
		std::shared_ptr<T> GetComponent()
		{
			//for (std::shared_ptr<BaseComponent> bc: m_pComponents)
			//{
			//	BaseComponent* rawBc = bc.get();
			//	if (typeid(*rawBc) == typeid(T))
			//	{
			//		//return dynamic_cast<T>(bc);
			//		return std::dynamic_pointer_cast<T>(bc);
			//	}
			//}
			if (m_pComponents.find(typeid(T)) != m_pComponents.end())
			{
				return m_pComponents[typeid(T)];
			}
			return nullptr;
		}
		template <typename T> void RemoveComponent()
		{
			//for (std::vector<std::shared_ptr<BaseComponent>>::iterator it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
			//{
			//	BaseComponent* rawBc = it->get();
			//	if (typeid(*rawBc) == typeid(T))
			//	{
			//		m_pComponents.erase(it);
			//	}
			//}
			const auto it = m_pComponents.find(typeid(T));
			if (it != m_pComponents.end())
			{
				m_pComponents.erase(it);
			}
		}

		//Base transform handling
		Transform& GetTransform();

		//Render handling
		void Render();
		bool IsVisual() const;
		void SetIsVisual(bool isVisual);

		//Child handling
		void AddChild(const std::shared_ptr<GameObject>& pChild);
		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(int index) const;
		void RemoveChild(int index);
		std::string GetName() const;
		void SetName(const std::string& name);

		//Owner handling
		void SetOwner(const std::weak_ptr<GameObject> owner);
		std::weak_ptr<GameObject> GetOwner() const;

		//C++ coding practice functions
		GameObject() = default;
		GameObject(std::string name);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		std::map<std::type_info ,std::shared_ptr<BaseComponent>> m_pComponents{};
		std::vector<std::shared_ptr<GameObject>> m_pChildObjects{};
		bool m_IsVisual{};
		Transform m_Transform{ weak_from_this() };

		std::string m_Name{};
		std::weak_ptr<GameObject> m_pOwner{};
	};
}
