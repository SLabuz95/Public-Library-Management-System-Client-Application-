#include"promptpanelcatchevents.hpp"
#include"promptpanel.hpp"
#include<QEvent>
#include"promptpanelminimizebutton.hpp"
#include"promptlist.hpp"
#include"promptpanelmaximizebutton.hpp"

PromptPanelCatchEvents::PromptPanelCatchEvents(PromptPanel* parent)
    : parent(parent){}

PromptPanelCatchEvents::~PromptPanelCatchEvents(){}

bool PromptPanelCatchEvents::eventFilter(QObject *obj, QEvent *ev){
    switch(*parent->getStatus()){
    case PROMPT_PANEL_HIDDEN:
        switch(ev->type()){
        case QEvent::MouseButtonRelease:
            if(obj == parent->getMinimizeButton()){
                parent->setStatus(*(parent->getStatus() + 1));
                return true;
            }
            break;
        default:
            break;
        }
        break;
    case PROMPT_PANEL_MAXIMIZED:
        switch(ev->type()){
        case QEvent::MouseButtonRelease:
            if(obj == parent->getMaximizeButton()){
                parent->setStatus(PROMPT_PANEL_MINIMIZED);
                return true;
            }
            if(obj == parent->getMinimizeButton()){
                parent->setStatus(PROMPT_PANEL_HIDDEN);
                return true;
            }
            parent->getPromptList()->matchEvents(obj, ev);
            return true;
            break;
        default:
            break;
        }
        break;
    case PROMPT_PANEL_MINIMIZED:
        switch(ev->type()){
        case QEvent::MouseButtonRelease:
            if(obj == parent->getMaximizeButton()){
                parent->setStatus(PROMPT_PANEL_MAXIMIZED);
                return true;
            }
            if(obj == parent->getMinimizeButton()){
                parent->setStatus(PROMPT_PANEL_HIDDEN);
                break;
            }
            parent->getPromptList()->matchEvents(obj, ev);
            return true;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj,ev);
}
