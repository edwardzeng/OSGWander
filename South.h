/* -*-c++-*- OpenSceneGraph - 2008.6.16 by FreeSouth
*
* RambleSystem操作器管理类，用来管理操作器
*/
//------------------------------//------------------------------
#pragma once
//------------------------------//------------------------------
#include <osgViewer/Viewer>
#include <osgGA/CameraManipulator>
#include <osgUtil/IntersectVisitor>
#include <osg/LineSegment>
//------------------------------//------------------------------
class CSouth: public osgGA::CameraManipulator
{
public:
	CSouth(void);
	~CSouth(void);
private:
	//结点值，用来测试碰撞检测的
	osg::ref_ptr<osg::Node> m_node;
	//相机操作器
	unsigned int m_nID;
	//移动速度
	float m_fMoveSpeed;
	//位置
	osg::Vec3 m_vPosition;
	//旋转角度
	osg::Vec3 m_vRotation;
	//左键是否按下
	bool m_bLeftButtonDown;
	//左键点下时屏幕坐标
	float m_fpushX;
	//碰撞检测开启状态查询。
	bool m_bPeng;
	//右键点下时屏幕坐标
	float m_fpushY;
public:
	//碰撞检测是否开启
	void setPeng(bool peng) ;
	//得到碰撞检测开启状态
	bool getPeng() ;
	//如果碰撞检测开启则关闭，如果关闭则开启
	void setFpeng() ;
	//设置要进行碰撞检测的数据
	virtual void setNode(osg::Node*);
	// 虚函数
	virtual void setByMatrix(const osg::Matrixd& matrix);
	// 虚函数
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);
	virtual osg::Matrixd getMatrix(void) const;
	// 得到逆矩阵
	virtual osg::Matrixd getInverseMatrix(void)const ;
	// 主要事件控制器
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
	// 屏目角度
	float m_fAngle;
	// 位置变换函数
	void ChangePosition(osg::Vec3& delta);
	//得到当前速度
	float getSpeed() ;
	//设置当前速度
	void setSpeed(float ) ;
	//设置视点位置
	void SetPosition(osg::Vec3 &position) ;
	void SetPosition(double *) ;
	//得到当前视点位置
	osg::Vec3 GetPosition() ;
	//计算家的位置
	void computeHomePosition();
};