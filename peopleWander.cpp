#include <osgViewer/Viewer>
#include <OSgDB/ReadFile>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>
#include <osgDB/FileUtils>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osgShadow/ShadowedScene>
#include <osgShadow/SoftShadowMap>
#include <iostream>
#include <osg/LightSource>
#include <istream>
#include <osg/AnimationPath>
#include <osgGA/NodeTrackerManipulator>

class OptionMd2: public osg::MatrixTransform
{
public:
	void toPosition(osg::Vec3 pos)
	{
		position=pos;
		setMatrix(osg::Matrix::translate(pos));
	}
	osg::Vec3 getpostion()
	{
		return position;
	}

	void rotateUP()
	{
		setMatrix((osg::Matrix::rotate(osg::inDegrees(-90.0f),osg::Vec3(0,1,0)*osg::Matrix::translate(position))));
	}

	void rotateDown()
	{
		setMatrix(osg::Matrix::rotate(osg::inDegrees(90.0f),osg::Vec3(0,1,0)*osg::Matrix::translate(position)));
	}

	vod rotateLeft()
	{
		setMatrix(osg::Matrix::rotate(osg::inDegrees(180.0f),osg::Vec3(0,1,0)*osg::Matrix::translate(position)));
	}

	vod rotateRight()
	{
		setMatrix(osg::Matrix::rotate(osg::inDegrees(0.0f),osg::Vec3(0,1,0)*osg::Matrix::translate(position)));
	}

private:
	osg::Vec3 position;
};

OptionMd2 *om= new OptionMd2;

class PickHander:public osgGA::GUIEventHandler
{
public:
	PickHander(osgViewer::Viewer *vt)
	{
		viewer=vt;
		controls=new osg::Vec3Array;
	}

	osg::Geode* CreateBox(osg::Vec3 center)
	{
		osg::ref_ptr<osg::Geode> gnode=new Geode;
		gnode->addDrawable(new osg::ShapeDrawable(new osg::Box(center,15,15,15)));
		return gnode.release();
	}
	float GetRunTime(osg::Vec3 res,osg::Vec3 des)
	{
		float distant=sqrt((des.x()-res.x())*(des.x()-res.x())+(des.z()-res.z()*(des.z()-res.z()));
		return distance*0.007;
	}

	osg::AnimationPath* CreatePath()
	{
		osg::ref_ptr<osg::AnimationPath> animationPath =new osg::AnimationPath;
		animationPath->setLoopMode(osg::AnimationPath::LOOP);
		float time=0.0;
		float angle=0.0;
		if(controls.valid())
		{
			osg::Vec3Array::iterator iter=controls->begin();
			for (;;)
			{
				osg::Vec3 postion(*iter);
				iter++;
				if(iter!=controls->end())
				{
					if(iter->x() > position.x())
					{
						angle=-atan((iter->z() - position.z())/(iter->x()-position.x()));
					}
					else
					{
						angle=-3.14-atan((iter->z()-position.z())/(iter->x()-position.x());
					}
					osg::Quat rotation(osg::Quat(angle,osg::Vec3(0.0,1.0,0.0)));
					animationPath->insert(time,osg::AnimationPath::ControlPoint(position,rotation));
					time+=GetRunTime(position,*iter);
				}
				else
				{
					break;
				}
			}
		}
		return animationPath.release();
	}
	bool handle(const osgGA::GUIActionAdapter& ea,osgGA::GUIActionAdapter& aa)
	{
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::DOUBLECLICK:
			{
				if(viewer)
				{
					osgUtil::LineSegmentIntersector::Intersections inters;
					if (viewer->computeIntersections(ea.getX(),ea.getY(),inters))
					{
						osgUtil::LineSegmentIntersector::Intersections::iterator iter=inters.begin();
						osg::Vec3 tempP;
						tempP.set(iter->getWorldIntersectPoint().x(),-24,iter->getWorldIntersectPoint().z());
						contrls->push_back(tempP);
						viewer->getSceneData()->asGroup()->addChild(CreateBox(tempP));
					}
				}
			}
			break;
		case osgGA::GUIEventAdapter::KEYDOWN:
			{
				if (ea.getKey()=='m'||ea.getKey()=='M')
				{
					om->setUpdateCallback(new osg::AnimationPathCallback(CreatePath(),0.0,1.0));
					osg::ref_ptr<osgGA::NodeTrackerManipulator> tm=new osgGA::NodeTrackerManipulator;
					tm->setTrackerMode(osgGA::NodeTrackerManipulator::TRACKBALL);
					tm->setTrackNode(om->getChild(0));
					viewer->setCameraManipulator(tm);
				}
			}
			break;
		default:
			break;
		}
	return false;
	}
private:
	osgViewer::Viewer* viewer;
	osg::ref_ptr<osg::Vec3Array> controls;
};

osg::Geode* CreateBox()
{
	osg::ref_ptr <osg::Geode> gnode=new osg::Geode;
	gnode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0, 24.0, 0.0), 1000,2,1000)));
	return gnode.release();
}

osg::Geode* CreateSphere(osg::Vec3 position)
{
	osg::ref_ptr<osg::Geode> gnode=new osg::Geode;
	gnode-> addDrawable (new osg::ShapeDrawable (new osg::Sphere(position,20)));
	return gnode.release();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer =new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root=new osg::Group;
	osgDB::FilePathList f1=osgDB::getDataFilePathList();
	f1.push_back(std::string(getenv("OSG_FILE_PATH"))+"\\s0\\");
	osgDB::setDataFilePathList(f1);

	osg::Switch* swtris =dynamic_cast<osg::Switch*>(osgDB::readNodeFile("./s0/tris.MD2"));
	osg::Switch* swweapon =dynamic_cast<osg::Switch*>(osgDB::readNodeFile("./s0/tris.MD2"));
	swtris->setAllChildrenOff();
	swweapon->setAllChildrenOff();
	swtris->setValue(1,true);
	swweapon->setValue(1,true);

	om->addChild(swtris);
	om->addChild(swweapon);

	osg::ref_ptr<osgShadow::ShadowedScene> ss=new osgShadow::ShadowedScene;
	ss->setShadowTechnique(new osgShadow::SoftShadowMap);
	ss->setReceivesShadowTraversalMask(0x01);
	ss->setCastsShadowTraversalMask(0x02);
	swtris->setNodeMask(0x02);
	swweapon->setNodeMask(0x02);
	osg::Geode* box=CreateBox();
	box->setNodeMask(0x01);
	ss->addChild(om);
	ss->addChild(box);

	osg::BoundingSphere bs =box->getBound();
	osg::Vec4 position= osg::Vec4(bs.center().x(),bs.center().y()-bs.radius(),bs.center().z()-bs.radius(),1.0f);
	osg::ref_ptr<osg::LightSource> ls=new osg::LightSource;
	ls->getLight()->setPosition(position);
	ls->getLight()->setAmbient(osg::Vec4(0.2,0.2,0.2,1.0));
	ls->getLight()->setDiffuse(osg::Vec4(0.8,0.8,0.8,1.0));
	ss->addChild(ls);

	root->addChild(ss);
	root->addChild(CreateSphere(osg::Vec3(position.x(),position.y(),position.z())));
	viewer->addEventHandler(new PickHander(viewer));
	viewer->setSceneData(root);
	viewer->run();
	return 0;
}


