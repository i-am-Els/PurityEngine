//
// Created by Eniola Olawale on 3/10/2024.
//

#pragma once

#include "purity_core_pch.h"

#include "layer_service.h"
#include "service_base.h"


namespace purity {
    constexpr size_t ARRAY_SIZE = 32;

    class PApplication;

    class Event;
    enum class ELayerType{
        Layer,
        OverlayLayer
    };

    class PURITY_API PLayerService final : public PServiceBase<ILayerService>{
        friend class PApplication;

    private:
        // ==================================================================================================
        // ====================================== START OF LAYER CLASS ======================================
        // ==================================================================================================
        class PURITY_API PLayer {
            friend class PLayerService;


            using CallbackFn = std::function<void()>;
            using CallbackFnWithEventArg1 = std::function<void(Event&)>;

        public:
            inline void enable() { m_enabled = true; }
            inline void disable() { m_enabled = false; }
            [[nodiscard]] [[maybe_unused]] inline bool isEnabled() const { return m_enabled; }

            explicit operator unsigned int() const { return m_id; }
            explicit operator std::string() const { return m_name;
            }

            PLayer() = delete;
            virtual ~PLayer() { PLog::echoMessage("Destroying Layer.");};
            PLayer& operator=(const PLayer& l) = delete; // copy assignment
            PLayer& operator=(PLayer&&) = delete; // move assignment

            void update();
            void attached();
            void detached();
            void eventFired(Event & event);

            [[maybe_unused]] void setAttachedCallback(CallbackFn callback);

            [[maybe_unused]] void setDetachedCallback(CallbackFn callback);

            [[maybe_unused]] void setUpdateCallback(CallbackFn callback);

            [[maybe_unused]] void setEventFireCallback(CallbackFnWithEventArg1 callback);
        private:
            PLayer(const PLayer& layer); // copy constructor
            PLayer(PLayer&& a) noexcept = default; // move constructor
            PLayer(unsigned int id, const std::string&);

            std::string m_name;
            unsigned int m_id;
            bool m_enabled;

            CallbackFn onUpdateCallback;
            CallbackFn onAttachedCallback;
            CallbackFn onDetachedCallback;
            CallbackFnWithEventArg1 onEventCallback;
        };
        // ========================================= END OF LAYERS =======================================
        // ===============================================================================================
        // ======================================= START OF ImGuiLayer =====================================


        class PURITY_API ImGuiLayer : public PLayer{
            friend class PLayerService;
            friend class PApplication;
        private:
        protected:
            ImGuiLayer(unsigned int id, const std::string& name);
            public:
            ImGuiLayer() = delete;

        };
        // ======================================== END OF ImGuiLayer ========================================
        // =================================================================================================
        // ================================== LAYER MANAGER CLASS DETAILS ==================================
    public:
        PLayerService(const PLayerService&) = delete;
        PLayerService(PLayerService&&) = delete;
        PLayerService& operator=(const PLayerService&) = delete;
        PLayerService& operator=(PLayerService&&) = delete;

        void exit() override;


        [[maybe_unused]] PLayer* fetchLayerByID(unsigned int id);

        [[maybe_unused]] PLayer* fetchLayerByName(const std::string &name);

        [[maybe_unused]] static bool s_IsReservedLayer(unsigned int layerIndex);
        ~PLayerService() noexcept override;

        void init() override;

        void destroy() override;

        PNT_TYPE_INDEX_DEF()
        PLayerService() = default;

    protected:
//        PLayerService() = default;

        /// Use this as interface
        [[maybe_unused]] [[nodiscard]] unsigned int s_CreateLayer(unsigned int id, const std::string& name, ELayerType layerType=ELayerType::Layer);

        /// Use this as interface
        [[maybe_unused]] bool deleteLayer(unsigned int id);
    private:

        // Do not use outside the LayerManager class
        void MakeLayer(ELayerType layerType, unsigned int id, const std::string& name);

    public:
        void preInit(std::any data) override;
        void postInit() override;
        void update(float deltaTime) override;

    private:
        static const unsigned int MAX_LAYER = ARRAY_SIZE;
        static const unsigned int BASE_LAYER_COUNT;
        std::array<PLayer*, MAX_LAYER> layerStack{};
    };
} // purity


