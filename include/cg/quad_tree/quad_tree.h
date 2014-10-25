#include <cg/primitives/point.h>

#include <vector>

namespace cg
{
    struct quad_tree
    {
        std::vector<quad_tree *> children;
        point_2 left_down_corner;
        point_2 right_up_corner;
        point_2 *point;


        quad_tree()
        {
            point = nullptr;
        }

        quad_tree(point_2 const &left_down_corner, point_2 const &right_up_corner)
                : left_down_corner(left_down_corner), right_up_corner(right_up_corner)
        {
            point = nullptr;
        }

        void add_point(point_2 new_point)
        {
            if (!is_square_consist_point(left_down_corner, right_up_corner, new_point))
            {
                return;
            }

            if (children.empty())
            {
                if (!point)
                {
                    point = new point_2(new_point);
                } else
                {
                    for (int i = 0; i < 4; i++)
                    {
                        children.push_back(new quad_tree());
                        ini_corners(children[i], i);
                        children[i]->add_point(new_point);
                        children[i]->add_point(*point);
                    }
                    point = nullptr;
                }
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    children[i]->add_point(new_point);
                }
            }
        }
        bool is_square_consist_point(point_2 left_down_corner, point_2 right_up_corner, point_2 point)
        {
            return left_down_corner.x <= point.x && left_down_corner.y <= point.y &&
                    right_up_corner.x > point.x && right_up_corner.y > point.y;
        }


        void ini_corners(quad_tree *q, int num_sq)
        {
            switch (num_sq)
            {
                case 0:
                    q->left_down_corner.x = (left_down_corner.x + right_up_corner.x) / 2;
                    q->left_down_corner.y = left_down_corner.y;
                    q->right_up_corner.x = right_up_corner.x;
                    q->right_up_corner.y = (left_down_corner.y + right_up_corner.y) / 2;
                    break;
                case 1:
                    q->left_down_corner.x = left_down_corner.x;
                    q->left_down_corner.y = left_down_corner.y;
                    q->right_up_corner.x = (left_down_corner.x + right_up_corner.x) / 2;
                    q->right_up_corner.y = (left_down_corner.y + right_up_corner.y) / 2;
                    break;
                case 2:
                    q->left_down_corner.x = left_down_corner.x;
                    q->left_down_corner.y = (left_down_corner.y + right_up_corner.y) / 2;
                    q->right_up_corner.x = (left_down_corner.x + right_up_corner.x) / 2;
                    q->right_up_corner.y = right_up_corner.y;
                    break;
                case 3:
                    q->left_down_corner.x = (left_down_corner.x + right_up_corner.x) / 2;
                    q->left_down_corner.y = (left_down_corner.y + right_up_corner.y) / 2;
                    q->right_up_corner.x = right_up_corner.x;
                    q->right_up_corner.y = right_up_corner.y;
                    break;
            }
        }

    };


}