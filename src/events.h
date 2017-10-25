#ifndef EVENTS_H
#define EVENTS_H

class Object {
    //EVENT_HELPER
};

class Event {
  Object *reciever;
  bool con = false;
  void (Object::*method)();
public:
  void Invoke() {
    if (con)
      (reciever ->*method)();
  }
  template <class RObject>
  Event(RObject* reciever,void (RObject::*call)()) {
    this -> reciever = reciever;
    this -> method = reinterpret_cast< void (Object::*)()> (call);
    con = true;
  }

  Event () {}
};


#endif
