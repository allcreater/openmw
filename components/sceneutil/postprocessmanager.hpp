#ifndef OPENMW_COMPONENTS_POSTPROCESSMANAGER_H
#define OPENMW_COMPONENTS_POSTPROCESSMANAGER_H

#include <osg/Group>
#include <osg/Camera>
#include <components/shader/shadermanager.hpp>

namespace SceneUtil
{

    class PostProcessManager : public osg::Camera
    {
    public:
        PostProcessManager(Shader::ShaderManager& shaderManager);
        PostProcessManager(const PostProcessManager& copy, const osg::CopyOp& copyop);

        //META_Object(NifOsg, PostProcessManager)

        virtual void traverse(osg::NodeVisitor& nv) override;

    private:
        //std::vector<osg::ref_ptr<osg::Camera>> mCameras;
        //std::vector<osg::ref_ptr<osg::Texture>> mTextures;
        osg::ref_ptr<osg::Geode> mGeode;

        unsigned int mTextureWidth, mTextureHeight;
    };

    osg::Group* createPostprocessSubgraph(Shader::ShaderManager& shaderManager, osg::Node* child);
}

#endif