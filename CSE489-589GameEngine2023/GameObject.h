#pragma once

#include <algorithm>

#include "SceneGraphNode.h"

/**
 * @enum	State
 *
 * @brief	An enumeration of the states of a game object.
 *
 * 			ACTIVE - Game object is in scene graph, and is is updated and "rendered"
 * 			PAUSED - Game object is in scene graph, but is not updated or "rendered"
 * 			DEAD - Game object will be removed from the game.
 */
enum STATE { ACTIVE, PAUSED, DEAD };

struct ReparentPair
{
	//std::shared_ptr<class GameObject> newParent;
	//std::shared_ptr<class GameObject> child;
	class GameObject* newParent;
	class GameObject* child;
	ReparentPair(class GameObject* newParent, class GameObject* child)
	//ReparentPair(std::shared_ptr<class GameObject>  newParent, std::shared_ptr<class GameObject> child)
	{
		this->newParent = newParent;
		this->child = child;
	}
};


class GameObject : public SceneGraphNode, public std::enable_shared_from_this<GameObject>
{
public:

	/**
	 * @fn	GameObject();
	 *
	 * @brief	Constructor
	 *
	 */
	GameObject();

	/**
	 * @fn	virtual ~GameObject();
	 *
	 * @brief	Destructor. Deletes all dynamically allocated memory.
	 */
	virtual ~GameObject();

	/**
	 * @fn	void GameObject::initialize();
	 *
	 * @brief	Initializes this game object and all attached components and any
	 * 			children of the game object.
	 */
	void initialize();

	/**
	 * @fn	virtual void GameObject::update(const float& deltaTime);
	 *
	 * @brief	Update function called from Game (not overridable). Updates this
	 * 			game object and all attached components.
	 *
	 * @param 	deltaTime	The time since the last update in seconds.
	 */
	virtual void update(const float& deltaTime);

	/**
	 * @fn	void GameObject::processInput();
	 *
	 * @brief	ProcessInput method called from Game (not overridable). Processes
	 * 			input for this game object and all attached.
	 */
	void processInput();

	/**
	 * @fn	void GameObject::addComponent(std::shared_ptr<class Component> component);
	 *
	 * @brief	Attaches a component to this game object
	 *
	 * @param 	component	If non-null, the component to attached.
	 */
	void addComponent(std::shared_ptr<class Component> component);

	/**
	 * @fn	void GameObject::removeComponent(std::shared_ptr<class Component> component);
	 *
	 * @brief	Detaches the component described by component from this game
	 * 			object
	 *
	 * @param 	component	If non-null, the component to be detached.
	 */
	void removeComponent(std::shared_ptr<class Component> component);

	/**
	 * @fn	STATE GameObject::getState() const
	 *
	 * @brief	Gets the state of the game object.
	 *
	 * @returns	The state of the game object.
	 */
	STATE getState() const { return gameObjectState; }

	/**
	 * @fn	void GameObject::setState(STATE state);
	 *
	 * @brief	Sets a state of the game object. Only ACTIVE game objects are
	 * 			updated and rendered. When the state of an object is set to DEAD,
	 * 			it will be deleted on the next update cycle.
	 *
	 * @param 	state	The state to which the object is being set.
	 */
	void setState(STATE state);

	/**
	 * @fn	std::vector<std::shared_ptr<class Component>> GameObject::getComponents()
	 *
	 * @brief	Returns the data structure containing all the Components attached
	 * 			to this GameObject.
	 *
	 * @returns	vector containing the components.
	 */
	std::vector<std::shared_ptr<class Component>> getComponents() { return components; }

	/**
	 * @fn	void GameObject::addChildGameObject(std::shared_ptr<class GameObject> gameObject);
	 *
	 * @brief	Adds a game object the game. The game object must not already be
	 * 			parented.
	 *
	 * @param [in]	gameObject	If non-null, the game object to be added.
	 */
	void addChildGameObject(std::shared_ptr<class GameObject> gameObject);

	/**
	 * @fn	void GameObject::removeAndDelete();
	 *
	 * @brief	Marks the GameObject for removal from the scene graph and
	 * 			deletion.
	 */
	void removeAndDelete();

	/**
	 * @fn	static std::shared_ptr<class Game> GameObject::getOwningGame()
	 *
	 * @brief	A game*.
	 *
	 * @returns	The owning game.
	 */
	static class Game* getOwningGame() { return OwningGame; }

	/**
	 * @fn	std::vector<std::shared_ptr<class GameObject>> GameObject::GetChildren();
	 *
	 * @brief	Gets the children GameObject of this item
	 *
	 * @returns	The children of the GameObject in the SceneGraph
	 */
	std::vector<std::shared_ptr<class GameObject>> GetChildren();

	/** @brief	Name of the game object. Should have and accessor and mutator methods. */
	std::string gameObjectName = "GameObject";

	/**
	 * @fn	void GameObject::reparent(std::shared_ptr<class GameObject> child);
	 *
	 * @brief	Adds a child to this GameObject. Removes the child from the
	 * 			children of the former parent. Local transformation is set so
	 * 			that the position and orientation relative to the World reference
	 * 			frame is unchanged. Set the parent of the child to "this"
	 * 			GameObject.
	 *
	 * @param [in]	child	- child that is being added.
	 */
	void reparent(class GameObject* child);

protected:

	/**
	 * @fn	static void GameObject::UpdateSceneGraph();
	 *
	 * @brief	Manage changes to the scene in the adding,
	 * 			removing, and reparenting GameObjects.
	 */
	static void UpdateSceneGraph();

	/**
	 * @fn	static void RemoveDeletedGameObjects();
	 *
	 * @brief	Removes the game objects that were deleted during the last
	 * 			update cycle.
	 */
	static void RemoveDeletedGameObjects();

	/**
	 * @fn	static void AddPendingGameObjects();
	 *
	 * @brief	Inserts game objects into the scene graph that were added 
	 * 			during the last update cycle.
	 */
	static void AddPendingGameObjects();

	/**
	 * @fn	static void ReparentGameObjects();
	 *
	 * @brief	Completes reparenting of game objects that were
	 * 			reparented during the last update cycle.
	 */
	static void ReparentGameObjects();

	/**
	* @fn	virtual void GameObjectInput();
	*
	* @brief	Any GameObject-specific input code (overridable). Called
	* 			by processInput
	*/
	//virtual void gameObjectInput();

	/**
	 * @fn	void updateGameObject(float deltaTime)
	 *
	 * @brief	Game object specific update based on deltaTime
	 *
	 * @param 	deltaTime	The delta time.
	 */
	//virtual void updateGameObject(const float & deltaTime);

	/** @brief	Current state of the game object */
	STATE gameObjectState = ACTIVE;

	/** @brief	The components that are attached to this game object. */
	std::vector<std::shared_ptr<class Component>> components;

	/** @brief	All the GameObjects in the Game */
	std::vector<std::shared_ptr<class GameObject>> children;

	/**
	 * @class	Game*
	 *
	 * @brief	The game that this game object is part of.
	 */
	static class Game* OwningGame;

	/** @brief	Any pending GameObjects that need to be added to the
	scene graph on the next update cycle. */
	static std::vector<std::shared_ptr<class GameObject>> PendingChildren;

	/** @brief	The dead game objects that need to be removed from
	the game on the next update cycle. */
	static std::vector<std::shared_ptr<class GameObject>> RemovedGameObjects;

	/** @brief	The game objects that are be attached to new
	parents after this update cycle.*/
	static std::vector<ReparentPair> ReparentedGameObjects;

}; // end GameObject class


