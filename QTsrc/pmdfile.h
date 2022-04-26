#ifndef PMDFILE_H
#define PMDFILE_H

#include "mmdfilestring.h"

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <array>

namespace mmd
{

    template <quint64 Size>
    using PMDString = mmd::MMDFileString<Size>;

    struct PMDHeader
    {
        PMDString<3>    m_magic;
        float           m_version;
        PMDString<20>   m_modelName;
        PMDString<256>  m_comment;

        uint8_t         m_haveEnglishNameExt;
        PMDString<20>   m_englishModelNameExt;
        PMDString<256>  m_englishCommentExt;
    };

    struct PMDVertex
    {
        QVector3D   m_position;
        QVector3D   m_normal;
        QVector2D   m_uv;
        quint16     m_bone[2];
        quint8      m_boneWeight;
        quint8      m_edge;
    };


    struct PMDFace
    {
        quint16 m_vertices[3];
    };

    struct PMDMaterial
    {
        QVector3D   m_diffuse;
        float       m_alpha;
        float       m_specularPower;
        QVector3D   m_specular;
        QVector3D   m_ambient;
        quint8      m_toonIndex;
        quint8      m_edgeFlag;
        quint32     m_faceVertexCount;
        PMDString<20> m_textureName;
    };

    struct PMDBone
    {
        PMDString<20>   m_boneName;
        quint16         m_parent;
        quint16         m_tail;
        quint8          m_boneType;
        qint16          m_ikParent;
        QVector3D       m_position;
        PMDString<20>   m_englishBoneNameExt;
    };

    struct PMDIk
    {
        quint16             m_ikNode;
        quint16             m_ikTarget;
        quint8              m_numChain;
        quint16             m_numIteration;
        float               m_rotateLimit;
        QVector<quint16>    m_chanins;
    };

    struct PMDMorph
    {
        struct PMDVertex
        {
            quint32     m_vertexIndex;
            QVector3D   m_position;
        };

        using VertexList = QVector<PMDVertex>;

        enum MorphType :quint8
        {
            Base,
            Eyebrow,
            Eye,
            Rip,
            Other,
        };

        PMDString<20>   m_morphName;
        MorphType       m_morphType;
        VertexList      m_vertices;
        PMDString<20>   m_englishShapeNameExt;
    };

    struct PMDMorphDisplayList
    {
        using DisplayList = QVector<quint16>;

        DisplayList m_displayList;
    };

    struct PMDBoneDisplayList
    {
        using DisplayList = QVector<quint16>;

        PMDString<50>   m_name;
        DisplayList     m_displayList;
        PMDString<50>   m_englishNameExt;
    };

    enum class PMDRigidBodyShape : quint8
    {
        Sphare,
        Box,
        Capsule,
    };

    enum class PMDRigidBodyOperation : quint8
    {
        Static,
        Dynamic,
        DynamicAdjustBone,
    };

    struct PMDRigidBodyExt
    {
        PMDString<20>   m_rigidBodyName;
        quint16         m_boneIndex;
        quint8          m_groupIndex;
        quint16         m_groupTarget;
        PMDRigidBodyShape m_shapeType;
        float           m_shapeWidth;
        float           m_shapeHeight;
        float           m_shapeDepth;
        QVector3D       m_pos;
        QVector3D       m_rot;
        float           m_rigidBodyWeight;
        float           m_rigidBodyPosDimmer;
        float           m_rigidBodyRotDimmer;
        float           m_rigidBodyRecoil;
        float           m_rigidBodyFriction;
        PMDRigidBodyOperation    m_rigidBodyType;
    };

    struct PMDJointExt
    {
        enum { NumJointName = 20 };

        PMDString<20>    m_jointName;
        quint32          m_rigidBodyA;
        quint32          m_rigidBodyB;
        QVector3D        m_jointPos;
        QVector3D        m_jointRot;
        QVector3D        m_constrainPos1;
        QVector3D        m_constrainPos2;
        QVector3D        m_constrainRot1;
        QVector3D        m_constrainRot2;
        QVector3D        m_springPos;
        QVector3D        m_springRot;
    };

    struct PMDFile
    {
        PMDHeader                       m_header;
        QVector<PMDVertex>              m_vertices;
        QVector<PMDFace>                m_faces;
        QVector<PMDMaterial>            m_materials;
        QVector<PMDBone>                m_bones;
        QVector<PMDIk>                  m_iks;
        QVector<PMDMorph>               m_morphs;
        PMDMorphDisplayList             m_morphDisplayList;
        QVector<PMDBoneDisplayList>     m_boneDisplayLists;
        std::array<PMDString<100>, 10>  m_toonTextureNames;
        QVector<PMDRigidBodyExt>        m_rigidBodies;
        QVector<PMDJointExt>            m_joints;
    };

    bool ReadPMDFile(PMDFile* pmdFile, const char* filename);
}
#endif // PMDFILE_H
