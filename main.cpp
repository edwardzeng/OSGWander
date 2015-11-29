//By FreeSouth ieysx@163.com www.osgChina.org 2008 6 13
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/ShapeDrawable>
#include "South.h"

osg::Geode* CreateStair()
{
	osg::ref_ptr<osg::Geode> gnode=new osg::Geode;
	for(int i=0;i<=20;++i)
	{
		osg::ref_ptr<osg::ShapeDrawable> shape=new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0,50.0+i*100,1.0+i*100),500.0,400.0,50.0));
		gnode->addDrawable(shape.get());
	}
	return gnode.release();
}

void main()
{
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> gp=new osg::Group;
	//gp->addChild(CreateStair());
	osg::ref_ptr<osg::Geode> sphere=new osg::Geode;
	sphere->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, -10.0f,1400.0f),100.0)));
	//gp->addChild(sphere);

	osg::ref_ptr<osg::Node> geode1=new osg::Node;
	geode1=osgDB::readNodeFile("E:/3rdpart/OSG/OpenSceneGraph/data/ceep.ive");
	gp->addChild(geode1);
	viewer.setSceneData(gp.get());
	//viewer.setSceneData(osgDB::readNodeFile("E:/SourceCode/OSG/OSGData/Robot/right/car.ive"));
	viewer.setCameraManipulator(new CSouth());
	viewer.realize();
	viewer.run();
}