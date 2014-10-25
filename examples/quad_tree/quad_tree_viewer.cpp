#include <QColor>
#include <QApplication>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/quad_tree/quad_tree.h>

using cg::point_2f;
using cg::point_2;
using cg::quad_tree;

struct quad_tree_viewer : cg::visualization::viewer_adapter
{
    quad_tree *qtree;

    quad_tree_viewer()
    {
        qtree = new quad_tree(point_2(-400, -400), point_2(400, 400));

    }

    void draw(cg::visualization::drawer_type & drawer) const
    {
        rec(drawer, qtree);
        
    }

    void print(cg::visualization::printer_type & p) const
    {

    }


    bool on_release(const point_2f & p)
    {
        qtree->add_point(p);
        return true;
    }

    bool on_key(int key)
    {

    }

    void rec(cg::visualization::drawer_type &drawer, quad_tree *ptree) const
    {
        if(!qtree)
        {
            return;
        }
        drawer.set_color(Qt::blue);
        drawer.draw_line(ptree->left_down_corner, point_2(ptree->right_up_corner.x, ptree->left_down_corner.y));
        drawer.draw_line(ptree->left_down_corner, point_2(ptree->left_down_corner.x, ptree->right_up_corner.y));
        drawer.draw_line(ptree->right_up_corner, point_2(ptree->left_down_corner.x, ptree->right_up_corner.y));
        drawer.draw_line(ptree->right_up_corner, point_2(ptree->right_up_corner.x, ptree->left_down_corner.y));
        if(ptree->point)
        {
            drawer.set_color(Qt::red);
            drawer.draw_point(*ptree->point, 5);
        }

        if(!ptree->children.empty())
        {
            for (int i = 0; i < 4; i++) {
               rec(drawer, ptree->children[i]);
            }
        }


    }


};

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    quad_tree_viewer viewer;
    cg::visualization::run_viewer(&viewer, "Quadtree");
}

