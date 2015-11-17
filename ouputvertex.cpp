#include <osgDB/ReadFile>
#include <osg/NodeVisitor>
#include <osg/Geometry>
#include <iostream>

class VertexExtractor:public osg::NodeVisitor
{
public:
	osg::ref_ptr<osg::Vec3Array> extracted_verts;
	VertexExtractor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{
		extracted_verts=new osg::Vec3Array;
	}
	void apply(osg::Geode& geode)
	{
		for (unsigned int i=0;i<geode.getNumDrawables();++i)
		{
			osg::Geometry* geom=dynamic_cast<osg::Geometry*>(geode.getDrawable(i));
			if(!geom)
			{
				continue;
			}
			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
			if(!verts)
			{
				continue;
			}
			extracted_verts->insert(extracted_verts->end(),verts->begin(),verts->end());
		}
	}
};

int main(int argc,char **argv)
{
	osg::Node* rootNode=osgDB::readNodeFile("glider.osg");
	VertexExtractor ivea;
	rootNode->accept(ivea);
	int size_t =ivea.extracted_verts.get()->size();
	std::vector<osg::Vec3>::iterator iter =ivea.extracted_verts.get()->begin();
	for (int i=0;i<size_t;++i)
	{
		std::cout<<iter->x()<<" "<<iter->y()<<" "<<iter->z()<<std::endl;
		iter++;
	}
	std::cout<<"finished outputing all vertex"<<st::endl;
	return 0;
}