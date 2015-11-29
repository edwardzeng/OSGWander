//By FreeSouth at 2008 6 16 ieysx@163.com www.osgChina.org
//------------------------------//------------------------------
#include "South.h"
//------------------------------//------------------------------
//设置一些初始值
CSouth::CSouth(void): m_fMoveSpeed(1.0f)
	//左键没有按下
	, m_bLeftButtonDown(false)
	//左键点下时初始坐标为0
	, m_fpushX(0)
	//初始角速度是2.5
	, m_fAngle(1.0)
	//开始时碰撞检测关闭
	, m_bPeng(false)
	//右键点下时初始坐标也为0
	, m_fpushY(0)
{
	//出生点为000
	//m_vPosition = osg::Vec3(20000.0, 1000,1000.0f);
	m_vPosition = osg::Vec3(0.0, 0.0,3.0f);
	//初始角度
	m_vRotation = osg::Vec3(2.0*osg::PI_4,0.0*osg::PI_4, 2.0*osg::PI_4);
}
//------------------------------//------------------------------
//析构函数
CSouth::~CSouth(void)
{ }
//------------------------------//------------------------------
void CSouth::setByMatrix(const osg::Matrixd & matrix)
{ }
//------------------------------//------------------------------
void CSouth::setByInverseMatrix(const osg::Matrixd& matrix)
{ }
//------------------------------//------------------------------
//得到矩阵，这是标准接口，用于控制场景
osg::Matrixd CSouth::getMatrix(void) const
{
	//得到旋转后的矩阵,其实也就是视口矩阵，用此控制场景
	osg::Matrixd mat;
	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),
		m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),
		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));
	return mat * osg::Matrixd::translate(m_vPosition);
}
//------------------------------//------------------------------
//得到逆矩阵，标准接口，控制场景
osg::Matrixd CSouth::getInverseMatrix(void) const
{
	osg::Matrixd mat;
	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),
		m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),
		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));
	return osg::Matrixd::inverse(mat * osg::Matrixd::translate(m_vPosition));
}
//------------------------------//------------------------------
//handle
bool CSouth::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us)
{
	//得到x的初始屏幕坐标
	float mouseX = ea.getX();
	//得到y的初始屏幕坐标
	float mouseY = ea.getY();
	//判断事件类型
	switch(ea.getEventType())
	{
		//如果是鼠标按下的事件
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			//如果是空格
			if (ea.getKey() == 'r'||ea.getKey() == 'R')
			{
				//重绘
				us.requestRedraw();
				us.requestContinuousUpdate(false);
				return true;
			}
			//如果是home键，则视点向上移动
			if (ea.getKey() == 0xFF50)//home
			{
				ChangePosition(osg::Vec3 (0, 0, m_fMoveSpeed)) ;
				return true;
			}
			//如果是end键，同视点向下移动
			if (ea.getKey() == 0xFF57) //end
			{
				ChangePosition(osg::Vec3 (0, 0, -m_fMoveSpeed)) ;
				return true;
			}
			//如果是加号键则加速
			if (ea.getKey() == 0x2B)//+
			{
				m_fMoveSpeed += 1.0f;
				return true;
			}
			//如果是减号键则减速
			if (ea.getKey() == 0x2D)//-
			{
				m_fMoveSpeed -= 1.0f;
				if (m_fMoveSpeed < 1.0f)
				{
					m_fMoveSpeed = 1.0f;
				}
				return true;
			}
			//向前走( 上箭头，W键)
			if (ea.getKey () == osgGA::GUIEventAdapter::KEY_W || ea.getKey () == 'W')//up
			{
				ChangePosition(osg::Vec3 (0, m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ;
				ChangePosition(osg::Vec3 (m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
				return true;
			}
			//向后退（下箭头，S键）
			if (ea.getKey () == osgGA::GUIEventAdapter::KEY_S || ea.getKey () == 'S' )//down
			{
				ChangePosition(osg::Vec3 (0, -m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ;
				ChangePosition(osg::Vec3(-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
				return true;
			}
			//A 左走
			if (ea.getKey () == osgGA::GUIEventAdapter::KEY_A ||ea.getKey () == 'A')
			{
				ChangePosition(osg::Vec3 (0, m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ;
				ChangePosition(osg::Vec3 (-m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
				return true;
			}
			//D 右走
			if (ea.getKey () == osgGA::GUIEventAdapter::KEY_D ||ea.getKey () == 'D')
			{
				ChangePosition(osg::Vec3 (0,-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ;
				ChangePosition(osg::Vec3 (m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
				return true;
			}
			//右箭头
			if (ea.getKey() == 0xFF53)
			{
				m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle);
			}
			//左箭头
			if (ea.getKey()== 0xFF51)
			{
				m_vRotation._v[2] += osg::DegreesToRadians(m_fAngle);
			}
			//F 旋转角速度减少0.2
			if (ea.getKey() == 'f' || ea.getKey() == 'F')
			{
				computeHomePosition();
				m_fAngle -= 0.2 ;
				return true ;
			}
			//G 旋转角速度增加0.2
			if (ea.getKey() == 'g' || ea.getKey() == 'G')
			{
				m_fAngle += 0.2 ;
				return true ;
			}
			//空格 回到原点
			if (ea.getKey() ==osgGA::GUIEventAdapter::KEY_Space)
			{
				computeHomePosition();
				return true ;
			}
			return false;
		}
		//单击
	case (osgGA::GUIEventAdapter ::PUSH ):
		//如果是左键，记录下来，因为左键拖动时场景也要转的
		if ( ea.getButton () == 1)
		{
			m_fpushX = mouseX ;
			m_fpushY = mouseY ;
			m_bLeftButtonDown = true ;
		}
		return false ;
		//拖动
	case (osgGA::GUIEventAdapter ::DRAG ):
		if ( m_bLeftButtonDown)
		{
			m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle * (mouseX-m_fpushX));
			m_vRotation._v[0] += osg::DegreesToRadians(0.01*(mouseY-m_fpushY)) ;
			//防止背过去
			if (m_vRotation._v [0] >= 3.14)
				m_vRotation._v [0] = 3.14 ;
			if (m_vRotation._v [0] <= 0)
				m_vRotation._v [0] = 0 ;
		}
		return false ;
		//键弹起
	case (osgGA::GUIEventAdapter ::RELEASE ):
		if ( ea.getButton () == 1)
		{
			m_bLeftButtonDown = false ;
		}
		return false ;
	default:
		return false;
	}
}
//------------------------------//------------------------------
//改变位置
void CSouth::ChangePosition(osg::Vec3 &delta)
{
	if (m_bPeng)
	{
		//看新值与旧值之间的连线是否与模型有交点！ 如果要到达的位置与现在的位置有交点的话，如果碰撞检测也开启了，就不移动
		osg::Vec3 newPos = m_vPosition + delta;
		osgUtil::IntersectVisitor iv;
		//前后的线段
		osg::ref_ptr<osg::LineSegment> line = new osg::LineSegment(newPos,m_vPosition);
		//上下移动的线段，加入两条线段来检测碰撞
		osg::ref_ptr<osg::LineSegment> lineZ = new osg::LineSegment(newPos + osg::Vec3(0.0f, 0.0f, m_fMoveSpeed),
			newPos - osg::Vec3(0.0f, 0.0f, m_fMoveSpeed));
		iv.addLineSegment(lineZ.get());
		iv.addLineSegment (line.get()) ;
		//接受碰撞的检测node
		m_node ->accept(iv);
		if (!iv.hits())
		{
			//如果没有碰撞，则移动旧位置到新的位置上
			m_vPosition += delta;
		}
	}
	else
		//如果碰撞检测根本没开，则直接移过去，
		m_vPosition += delta;
}
//------------------------------//------------------------------
//得到移动速度
float CSouth::getSpeed()
{
	return m_fMoveSpeed ;
}
//------------------------------//------------------------------
//设置移动速度
void CSouth::setSpeed(float sp)
{
	m_fMoveSpeed = sp ;
}
//------------------------------//------------------------------
//设置视口所在位置
void CSouth::SetPosition(osg::Vec3 &position)
{
	m_vPosition = position ;
}
void CSouth::SetPosition(double* position)
{
	m_vPosition._v[0] = position[0] ;
	m_vPosition._v[1] = position[1] ;
	m_vPosition._v[2] = position[2] ;
}
//------------------------------//------------------------------
//得到视口所在位置
osg::Vec3 CSouth::GetPosition()
{
	return m_vPosition ;
}
//------------------------------//------------------------------
//设置碰撞检测所起作用的物体
void CSouth::setNode(osg::Node* node)
{
	m_node = node ;
}
//------------------------------//------------------------------
//计算家的位置，其实是包围球的球心处
void CSouth::computeHomePosition()
{
	//如果有模型，则计算包围球的球心
	if(m_node.get())
	{
		const osg::BoundingSphere& boundingSphere=m_node ->getBound();
		osg::Vec3 bp = boundingSphere._center;
		SetPosition(bp) ;
	}
}
//------------------------------//------------------------------
//设置碰撞检测为开启或者关闭
void CSouth::setPeng(bool peng)
{
	m_bPeng = peng ;
}
//------------------------------//------------------------------
//得到碰撞检测的状态
bool CSouth::getPeng()
{
	return m_bPeng ;
}
//------------------------------//------------------------------
//如果碰撞测试在开启，则关闭它，如果在关闭，则开启它
void CSouth::setFpeng()
{
	m_bPeng = !m_bPeng ;
}