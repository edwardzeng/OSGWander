/* -*-c++-*- OpenSceneGraph - 2008.6.16 by FreeSouth
*
* RambleSystem�����������࣬�������������
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
	//���ֵ������������ײ����
	osg::ref_ptr<osg::Node> m_node;
	//���������
	unsigned int m_nID;
	//�ƶ��ٶ�
	float m_fMoveSpeed;
	//λ��
	osg::Vec3 m_vPosition;
	//��ת�Ƕ�
	osg::Vec3 m_vRotation;
	//����Ƿ���
	bool m_bLeftButtonDown;
	//�������ʱ��Ļ����
	float m_fpushX;
	//��ײ��⿪��״̬��ѯ��
	bool m_bPeng;
	//�Ҽ�����ʱ��Ļ����
	float m_fpushY;
public:
	//��ײ����Ƿ���
	void setPeng(bool peng) ;
	//�õ���ײ��⿪��״̬
	bool getPeng() ;
	//�����ײ��⿪����رգ�����ر�����
	void setFpeng() ;
	//����Ҫ������ײ��������
	virtual void setNode(osg::Node*);
	// �麯��
	virtual void setByMatrix(const osg::Matrixd& matrix);
	// �麯��
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);
	virtual osg::Matrixd getMatrix(void) const;
	// �õ������
	virtual osg::Matrixd getInverseMatrix(void)const ;
	// ��Ҫ�¼�������
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
	// ��Ŀ�Ƕ�
	float m_fAngle;
	// λ�ñ任����
	void ChangePosition(osg::Vec3& delta);
	//�õ���ǰ�ٶ�
	float getSpeed() ;
	//���õ�ǰ�ٶ�
	void setSpeed(float ) ;
	//�����ӵ�λ��
	void SetPosition(osg::Vec3 &position) ;
	void SetPosition(double *) ;
	//�õ���ǰ�ӵ�λ��
	osg::Vec3 GetPosition() ;
	//����ҵ�λ��
	void computeHomePosition();
};