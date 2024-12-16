//
// Created by Eniola Olawale on 3/10/2024.
//

#pragma once

#include "layer.h"

namespace purity {

    /// @brief A LayerMask is a bit representation of a initialLayerIndex of Layers
    /// @details The way the LayerMask works; It is a bit representation of 32 Layers, the first layer having index 0 and the last layer has index 31.
    /// For each Layer added to the LayerMask, the bit at the layerIndex is set to 1, while Layers that are excluded have bits set to 0.
    /// @remarks When dealing with LayerMasks, think in Binary and use Bitwise operators. The constructor takes the first layerIndex you wish to add to the
    /// LayerMask. The static creator takes a mask with all your layers already, it is expected that you've added all the Layers
    /// via Bitwise operators already, it only returns a LayerMask object of the mask.
    class PURITY_API LayerMask {
    public:
        explicit LayerMask(unsigned int initialLayerIndex);
        [[nodiscard]] std::vector<int> getIncludedLayers() const;
        bool addLayer(int layerIndex);
        bool removeLayer(int layerIndex);
        [[nodiscard]] unsigned int getMaskContent() const;
        /// Destructor
        ~LayerMask();

        operator unsigned int() const { return content; }
        [[maybe_unused]] static LayerMask s_CreateLayerMask(unsigned int mask);

    private:
        unsigned int content;

    };

} // purity

