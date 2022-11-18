#pragma once

#include "../singleton.h"
#include <QObject>
#include <QLinkedList>

#include "action.h"
#include "state.h"
#include "subscriber.h"

namespace Qux {
	namespace Redux	{
		class Store : public QObject, public Qux::Singleton<Store>
		{
			Q_OBJECT

			Q_SIGNALS :
			void signalSendReducer(Action _action, State _state);

			public Q_SLOTS:
			void slotChangeState(State _new_state) {
				state_ = _new_state;
				for (auto x : subscribers_)
				{
					x->changeState(_new_state);
				}
			}


		public:
			friend Store& Singleton<Store>::inst();
			Store() {}
			State& getState() { return state_; }
			void dispatch(Action _action) { emit signalSendReducer(_action, state_); }
			void regSubscriber(ISubscriber* _sub) { subscribers_.append(_sub); }
			void unregSubscriber(ISubscriber* _sub) { subscribers_.removeOne(_sub); }

		protected:
			State state_;
			QLinkedList<ISubscriber*> subscribers_;
		};
	}
}
