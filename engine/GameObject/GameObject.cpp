#include "GameObject.h"

GameObject::GameObject(const std::string& _typeName, const std::string& _objectName)
: typeName(_typeName), objectName(_objectName)
 {
 	
 }

 GameObject::GameObject(GameObject&& go)
 : typeName(std::move(go.typeName)), objectName(std::move(go.objectName))
 {
 	animation = go.animation;
 	image = go.image;
 	text = go.text;
 	position = go.position;
 	movement = go.movement;
 }

 GameObject::~GameObject()
 {

 }