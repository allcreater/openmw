#include "postprocessmanager.hpp"

#include <osgUtil/CullVisitor>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/TextureRectangle>
#include <osg/PolygonMode>

namespace SceneUtil
{
    static osg::Geometry* makeFullscreenQuad()
    {
        return osg::createTexturedQuadGeometry(osg::Vec3(-1, -1, 0), osg::Vec3(2, 0, 0), osg::Vec3(0, 2, 0));
    }

    static osg::Texture* makeRTTTexture()
    {
        osg::TextureRectangle* texture = new osg::TextureRectangle();
        texture->setBorderWidth(0);
        texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::NEAREST);
        texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::NEAREST);
        texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_BORDER);
        texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_BORDER);

        texture->setTextureWidth(1024);
        texture->setTextureHeight(768);

        texture->setInternalFormat(GL_RGBA32F_ARB);
        texture->setSourceType(GL_FLOAT);
        texture->setSourceFormat(GL_RGBA);
        return texture;
    }

    PostProcessManager::PostProcessManager(Shader::ShaderManager& shaderManager)
        : osg::Camera()
    {
        osg::Texture* texture = makeRTTTexture();
        //mTextures.push_back(texture);

        setReferenceFrame(osg::Transform::RELATIVE_RF);
        setViewMatrix(osg::Matrix());
        setProjectionMatrix(osg::Matrix());
        setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
        setClearColor(osg::Vec4());
        //setRenderTargetImplementation(osg::Camera::RenderTargetImplementation::SEPARATE_WINDOW);
        attach(osg::Camera::BufferComponent::COLOR_BUFFER0, texture);
        setRenderOrder(osg::Camera::PRE_RENDER);
        

        auto quad = makeFullscreenQuad();
        
        quad->setCullingActive(false);
        quad->getOrCreateStateSet()->setTextureAttribute(0, texture);
        quad->getOrCreateStateSet()->addUniform(new osg::Uniform("color1", 0));
        //quad->getOrCreateStateSet()->setTextureAttribute(1, tex2);
        //quad->getOrCreateStateSet()->addUniform(new osg::Uniform("color2", 1));

        auto sp = shaderManager.getProgram(
            shaderManager.getShader("postprocessTest_vertex.glsl", std::map<std::string, std::string>(), osg::Shader::VERTEX),
            shaderManager.getShader("postprocessTest_fragment.glsl", std::map<std::string, std::string>(), osg::Shader::FRAGMENT)
        );
        quad->getOrCreateStateSet()->setAttributeAndModes(sp);
        quad->getOrCreateStateSet()->setMode(GL_CULL_FACE, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
        quad->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
        quad->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
        quad->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
        quad->getOrCreateStateSet()->setAttribute(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL));

        mGeode = new osg::Geode();
        mGeode->setCullingActive(false);
        mGeode->addDrawable(quad);
    }

    PostProcessManager::PostProcessManager(const PostProcessManager& copy, const osg::CopyOp& copyop)
        : osg::Camera(copy, copyop)
    {
    }

    void PostProcessManager::traverse(osg::NodeVisitor& nv)
    {
        osgUtil::CullVisitor* pCV = dynamic_cast<osgUtil::CullVisitor*>(&nv);
        if (pCV == nullptr)
            return osg::Camera::traverse(nv);
        
        //bool needUpdate = false;
        //const osg::Viewport* vp = pCV->getViewport();
        //if (vp->width() != mTextureWidth || vp->height() != mTextureHeight)
        //{
        //    for (auto& tex : mTextures)
        //    {
        //        auto tr = dynamic_cast<osg::TextureRectangle*>(tex.get());
        //        tr->setTextureHeight(vp->height());
        //        tr->setTextureWidth(vp->width());
        //        tr->dirtyTextureObject();
        //    }

        //    mTextureWidth = vp->width();
        //    mTextureHeight = vp->height();
        //    needUpdate = true;
        //}

        osg::Camera::traverse(nv);
        //mGeode->accept(nv);
    }

    osg::Group* createPostprocessSubgraph(Shader::ShaderManager& shaderManager, osg::Node* child)
    {
        //auto quad = makeFullscreenQuad();

        //quad->setCullingActive(false);
        ////quad->getOrCreateStateSet()->setTextureAttribute(0, texture);
        //quad->getOrCreateStateSet()->addUniform(new osg::Uniform("color1", 0));
        ////quad->getOrCreateStateSet()->setTextureAttribute(1, tex2);
        ////quad->getOrCreateStateSet()->addUniform(new osg::Uniform("color2", 1));

        //auto sp = shaderManager.getProgram(
        //    shaderManager.getShader("postprocessTest_vertex.glsl", std::map<std::string, std::string>(), osg::Shader::VERTEX),
        //    shaderManager.getShader("postprocessTest_fragment.glsl", std::map<std::string, std::string>(), osg::Shader::FRAGMENT)
        //);
        //quad->getOrCreateStateSet()->setAttributeAndModes(sp);
        //quad->getOrCreateStateSet()->setMode(GL_CULL_FACE, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
        //quad->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
        //quad->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
        //quad->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
        //quad->getOrCreateStateSet()->setAttribute(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL));

        //auto g = new osg::Geode();
        //g->setCullingActive(false);
        //g->addDrawable(quad);
        //

        //auto postprocessRoot = new SceneUtil::PostProcessManager(shaderManager);
        //postprocessRoot->addChild(child);
        ////return postprocessRoot;

        //g->addChild(postprocessRoot);
        //return g;

        osg::Texture* tex1 = makeRTTTexture();
        osg::Texture* tex2 = makeRTTTexture();

        osg::Texture* texDepth = makeRTTTexture();
        texDepth->setInternalFormat(GL_DEPTH_COMPONENT32F);
        texDepth->setSourceFormat(GL_DEPTH_COMPONENT);

        osg::Camera* cam = new osg::Camera();
        cam->setNodeMask(1 << 15);
        cam->setReferenceFrame(osg::Transform::RELATIVE_RF);
        cam->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
        cam->attach(osg::Camera::BufferComponent::COLOR_BUFFER0, tex1);
        cam->attach(osg::Camera::BufferComponent::COLOR_BUFFER1, tex2);
        cam->attach(osg::Camera::BufferComponent::DEPTH_BUFFER, texDepth);
        cam->setRenderOrder(osg::Camera::PRE_RENDER);
        cam->addChild(child);

        auto quad = makeFullscreenQuad();
        quad->setCullingActive(false);
        quad->getOrCreateStateSet()->setTextureAttribute(0, tex1);
        quad->getOrCreateStateSet()->addUniform(new osg::Uniform("bufferColor", 0));
        quad->getOrCreateStateSet()->setTextureAttribute(1, tex2);
        quad->getOrCreateStateSet()->addUniform(new osg::Uniform("bufferNormalShininess", 1));
        quad->getOrCreateStateSet()->setTextureAttribute(2, texDepth);
        quad->getOrCreateStateSet()->addUniform(new osg::Uniform("bufferDepth", 2));
        auto sp = shaderManager.getProgram(
            shaderManager.getShader("postprocessTest_vertex.glsl", std::map<std::string, std::string>(), osg::Shader::VERTEX),
            shaderManager.getShader("postprocessTest_fragment.glsl", std::map<std::string, std::string>(), osg::Shader::FRAGMENT)
        );
        quad->getOrCreateStateSet()->setAttributeAndModes(sp, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);

        auto geode = new osg::Geode();
        geode->setCullingActive(false);
        geode->addDrawable(quad);
        geode->addChild(cam);
        geode->setNodeMask(1 << 15);
        
        return geode;
    }
}