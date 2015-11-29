//By FreeSouth at 2008 6 16 ieysx@163.com www.osgChina.org
//------------------------------//------------------------------
#include "South.h"
//------------------------------//------------------------------
//����һЩ��ʼֵ
CSouth::CSouth(void): m_fMoveSpeed(1.0f)
	//���û�а���
	, m_bLeftButtonDown(false)
	//�������ʱ��ʼ����Ϊ0
	, m_fpushX(0)
	//��ʼ���ٶ���2.5
	, m_fAngle(1.0)
	//��ʼʱ��ײ���ر�
	, m_bPeng(false)
	//�Ҽ�����ʱ��ʼ����ҲΪ0
	, m_fpushY(0)
{
	//������Ϊ000
	//m_vPosition = osg::Vec3(20000.0, 1000,1000.0f);
	m_vPosition = osg::Vec3(0.0, 0.0,3.0f);
	//��ʼ�Ƕ�
	m_vRotation = osg::Vec3(2.0*osg::PI_4,0.0*osg::PI_4, 2.0*osg::PI_4);
}
//------------------------------//------------------------------
//��������
CSouth::~CSouth(void)
{ }
//------------------------------//------------------------------
void CSouth::setByMatrix(const osg::Matrixd & matrix)
{ }
//------------------------------//------------------------------
void CSouth::setByInverseMatrix(const osg::Matrixd& matrix)
{ }
//------------------------------//------------------------------
//�õ��������Ǳ�׼�ӿڣ����ڿ��Ƴ���
osg::Matrixd CSouth::getMatrix(void) const
{
	//�õ���ת��ľ���,��ʵҲ�����ӿھ����ô˿��Ƴ���
	osg::Matrixd mat;
	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),
		m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),
		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));
	return mat * osg::Matrixd::translate(m_vPosition);
}
//------------------------------//------------------------------
//�õ�����󣬱�׼�ӿڣ����Ƴ���
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
	//�õ�x�ĳ�ʼ��Ļ����
	float mouseX = ea.getX();
	//�õ�y�ĳ�ʼ��Ļ����
	float mouseY = ea.getY();
	//�ж��¼�����
	switch(ea.getEventType())
	{
		//�������갴�µ��¼�
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			//����ǿո�
			if (ea.getKey() == 'r'||ea.getKey() == 'R')
			{
				//�ػ�
				us.requestRedraw();
				us.requestContinuousUpdate(false);
				return true;
			}
			//�����home�������ӵ������ƶ�
			if (ea.getKey() == 0xFF50)//home
			{
				ChangePosition(osg::Vec3 (0, 0, m_fMoveSpeed)) ;
				return true;
			}
			//�����end����ͬ�ӵ������ƶ�
			if (ea.getKey() == 0xFF57) //end
			{
				ChangePosition(osg::Vec3 (0, 0, -m_fMoveSpeed)) ;
				return true;
			}
			//����ǼӺż������
			if (ea.getKey() == 0x2B)//+
			{
				m_fMoveSpeed += 1.0f;
				return true;
			}
			//����Ǽ��ż������
			if (ea.getKey() == 0x2D)//-
			{
				m_fMoveSpeed -= 1.0f;
				if (m_fMoveSpeed < 1.0f)
				{
					m_fMoveSpeed = 1.0f;
				}
				return true;
			}
			//��ǰ��( �ϼ�ͷ��W��)
			if (ea.getKey () == osgGA::GUIEventAdapter::KEY_W || ea.getKey () == 'W')//up
			{
				ChangePosition(osg::Vec3 (0, m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ;
				ChangePosition(osg::Vec3 (m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
				return true;
			}
			//����ˣ��¼�ͷ��S����
			if (ea.getKey () == osgGA::GUIEventAdapter::KEY_S || ea.getKey () == 'S' )//down
			{
				ChangePosition(osg::Vec3 (0, -m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ;
				ChangePosition(osg::Vec3(-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
				return true;
			}
			//A ����
			if (ea.getKey () == osgGA::GUIEventAdapter::KEY_A ||ea.getKey () == 'A')
			{
				ChangePosition(osg::Vec3 (0, m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ;
				ChangePosition(osg::Vec3 (-m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
				return true;
			}
			//D ����
			if (ea.getKey () == osgGA::GUIEventAdapter::KEY_D ||ea.getKey () == 'D')
			{
				ChangePosition(osg::Vec3 (0,-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ;
				ChangePosition(osg::Vec3 (m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
				return true;
			}
			//�Ҽ�ͷ
			if (ea.getKey() == 0xFF53)
			{
				m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle);
			}
			//���ͷ
			if (ea.getKey()== 0xFF51)
			{
				m_vRotation._v[2] += osg::DegreesToRadians(m_fAngle);
			}
			//F ��ת���ٶȼ���0.2
			if (ea.getKey() == 'f' || ea.getKey() == 'F')
			{
				computeHomePosition();
				m_fAngle -= 0.2 ;
				return true ;
			}
			//G ��ת���ٶ�����0.2
			if (ea.getKey() == 'g' || ea.getKey() == 'G')
			{
				m_fAngle += 0.2 ;
				return true ;
			}
			//�ո� �ص�ԭ��
			if (ea.getKey() ==osgGA::GUIEventAdapter::KEY_Space)
			{
				computeHomePosition();
				return true ;
			}
			return false;
		}
		//����
	case (osgGA::GUIEventAdapter ::PUSH ):
		//������������¼��������Ϊ����϶�ʱ����ҲҪת��
		if ( ea.getButton () == 1)
		{
			m_fpushX = mouseX ;
			m_fpushY = mouseY ;
			m_bLeftButtonDown = true ;
		}
		return false ;
		//�϶�
	case (osgGA::GUIEventAdapter ::DRAG ):
		if ( m_bLeftButtonDown)
		{
			m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle * (mouseX-m_fpushX));
			m_vRotation._v[0] += osg::DegreesToRadians(0.01*(mouseY-m_fpushY)) ;
			//��ֹ����ȥ
			if (m_vRotation._v [0] >= 3.14)
				m_vRotation._v [0] = 3.14 ;
			if (m_vRotation._v [0] <= 0)
				m_vRotation._v [0] = 0 ;
		}
		return false ;
		//������
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
//�ı�λ��
void CSouth::ChangePosition(osg::Vec3 &delta)
{
	if (m_bPeng)
	{
		//����ֵ���ֵ֮��������Ƿ���ģ���н��㣡 ���Ҫ�����λ�������ڵ�λ���н���Ļ��������ײ���Ҳ�����ˣ��Ͳ��ƶ�
		osg::Vec3 newPos = m_vPosition + delta;
		osgUtil::IntersectVisitor iv;
		//ǰ����߶�
		osg::ref_ptr<osg::LineSegment> line = new osg::LineSegment(newPos,m_vPosition);
		//�����ƶ����߶Σ����������߶��������ײ
		osg::ref_ptr<osg::LineSegment> lineZ = new osg::LineSegment(newPos + osg::Vec3(0.0f, 0.0f, m_fMoveSpeed),
			newPos - osg::Vec3(0.0f, 0.0f, m_fMoveSpeed));
		iv.addLineSegment(lineZ.get());
		iv.addLineSegment (line.get()) ;
		//������ײ�ļ��node
		m_node ->accept(iv);
		if (!iv.hits())
		{
			//���û����ײ�����ƶ���λ�õ��µ�λ����
			m_vPosition += delta;
		}
	}
	else
		//�����ײ������û������ֱ���ƹ�ȥ��
		m_vPosition += delta;
}
//------------------------------//------------------------------
//�õ��ƶ��ٶ�
float CSouth::getSpeed()
{
	return m_fMoveSpeed ;
}
//------------------------------//------------------------------
//�����ƶ��ٶ�
void CSouth::setSpeed(float sp)
{
	m_fMoveSpeed = sp ;
}
//------------------------------//------------------------------
//�����ӿ�����λ��
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
//�õ��ӿ�����λ��
osg::Vec3 CSouth::GetPosition()
{
	return m_vPosition ;
}
//------------------------------//------------------------------
//������ײ����������õ�����
void CSouth::setNode(osg::Node* node)
{
	m_node = node ;
}
//------------------------------//------------------------------
//����ҵ�λ�ã���ʵ�ǰ�Χ������Ĵ�
void CSouth::computeHomePosition()
{
	//�����ģ�ͣ�������Χ�������
	if(m_node.get())
	{
		const osg::BoundingSphere& boundingSphere=m_node ->getBound();
		osg::Vec3 bp = boundingSphere._center;
		SetPosition(bp) ;
	}
}
//------------------------------//------------------------------
//������ײ���Ϊ�������߹ر�
void CSouth::setPeng(bool peng)
{
	m_bPeng = peng ;
}
//------------------------------//------------------------------
//�õ���ײ����״̬
bool CSouth::getPeng()
{
	return m_bPeng ;
}
//------------------------------//------------------------------
//�����ײ�����ڿ�������ر���������ڹرգ�������
void CSouth::setFpeng()
{
	m_bPeng = !m_bPeng ;
}