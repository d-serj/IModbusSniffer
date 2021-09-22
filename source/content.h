/**
 * @file   init.h
 * @brief  
 */

#ifndef CONTENT_H_
#define CONTENT_H_

#include <vector>


class View;

class Content
{
public:
    Content();
    ~Content();

    std::vector<View*>& get_views();

private:

};

#endif // CONTENT_H_

