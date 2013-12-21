#ifndef _MY_CCMENU_H_
#define _MY_CCMENU_H_
#include "cocos2d.h"

class MyCCMenu : public cocos2d::CCMenu
{
public:

	


	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	static MyCCMenu* create();

    /** creates a CCMenu with CCMenuItem objects 
     * @lua NA
     */
    static MyCCMenu* create(cocos2d::CCMenuItem* item, ...);

    /** creates a CCMenu with a CCArray of CCMenuItem objects 
     * @js NA
     */
    static MyCCMenu* createWithArray(cocos2d::CCArray* pArrayOfItems);

    /** creates a CCMenu with it's item, then use addChild() to add 
      * other items. It is used for script, it can't init with undetermined
      * number of variables.
      * @js NA
    */
    static MyCCMenu* createWithItem(cocos2d::CCMenuItem* item);
    
    /** creates a CCMenu with CCMenuItem objects 
     * @js NA
     * @lua NA
     */
    static MyCCMenu* createWithItems(cocos2d::CCMenuItem *firstItem, va_list args);

	cocos2d::CCPoint lastTouch;
	
};

#endif