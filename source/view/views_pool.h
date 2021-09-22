/**
 * @file   views_pool.h
 * @brief  
 */

#ifndef VIEVS_POOL_H_
#define VIEVS_POOL_H_

#include <vector>

class View;

 /* View Registry. Allows adding of new windows */
struct ViewsPool
{
    ViewsPool();
    ~ViewsPool();

    /**
     * @brief Get pool of views.
     * @return reference to the vector of views
     */
    static std::vector<View*>& get_pool();

    /**
     * @brief Add view to the pool
     * @param view .. pointer to the view
     */
    static void add(View* view);

private:
    
    /** Pool of views that are available in the app */
    static std::vector<View*> views;
};


#endif // VIEVS_POOL_H_

