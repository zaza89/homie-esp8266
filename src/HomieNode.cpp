#include "HomieNode.h"

using namespace HomieInternals;

HomieNode::HomieNode(const char* id, const char* type, NodeInputHandler inputHandler, bool subscribeToAll)
: _inputHandler(inputHandler)
, _subscriptionsCount(0)
, _subscribeToAll(subscribeToAll) {
  if (strlen(id) + 1 > MAX_NODE_ID_LENGTH || strlen(type) + 1 > MAX_NODE_TYPE_LENGTH) {
    Serial.println(F("✖ HomieNode(): either the id or type string is too long"));
    abort();
  }

  this->_id = id;
  this->_type = type;
}

void HomieNode::subscribe(const char* property, PropertyInputHandler inputHandler) {
  if (this->_subscribeToAll) return;

  if (strlen(property) + 1 > MAX_NODE_PROPERTY_LENGTH) {
    Serial.println(F("✖ subscribe(): the property string is too long"));
    abort();
  }

  if (this->_subscriptionsCount > MAX_SUBSCRIPTIONS_COUNT_PER_NODE) {
    Serial.println(F("✖ subscribe(): the max subscription count has been reached"));
    abort();
  }

  Subscription subscription;
  strcpy(subscription.property, property);
  subscription.inputHandler = inputHandler;
  this->_subscriptions[this->_subscriptionsCount++] = subscription;
}

const char* HomieNode::getId() const {
  return this->_id;
}

const char* HomieNode::getType() const {
  return this->_type;
}

const Subscription* HomieNode::getSubscriptions() const {
  return this->_subscriptions;
}

unsigned char HomieNode::getSubscriptionsCount() const {
  return this->_subscriptionsCount;
}

bool HomieNode::getSubscribeToAll() const {
  return this->_subscribeToAll;
}

NodeInputHandler HomieNode::getInputHandler() const {
  return this->_inputHandler;
}
