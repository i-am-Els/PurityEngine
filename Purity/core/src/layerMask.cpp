// //
// // Created by Eniola Olawale on 3/10/2024.
// //
//
// #include "layerMask.h"
//
// namespace purity {
//
//     /// To create a layerMask, start with an initial layer index
//     LayerMask::LayerMask(unsigned int initialLayerIndex) {
//         content = (1 << initialLayerIndex);
//     }
//
//     std::vector<int> LayerMask::getIncludedLayers() const {
//         auto arr = std::vector<int>();
//
//         for(unsigned int i = 0; i < sizeof(content) * 8; i++){
//             if ((content >> i) & 1)
//                 arr.push_back(int(i));
//         }
//         return arr;
//     }
//
//     bool LayerMask::addLayer(int layerIndex) {
//         if (layerIndex <= 31){
//             content = content | (1 << layerIndex);
//             return true;
//         }
//         return false;
//     }
//
//     LayerMask::~LayerMask(){
//         PLog::echoMessage("Destroying Layer Mask.");
//     }
//
//     /// False tells that the layer was not added to the max at all in the first place
//     bool LayerMask::removeLayer(int layerIndex) {
//         if ((content >> layerIndex) & 1){
//             content &= ~(1 << layerIndex);
//             return true;
//         }
//         return false;
//     }
//
//     [[maybe_unused]] LayerMask LayerMask::s_CreateLayerMask(unsigned int mask) {
//         /// Mask Should never be Zero;
//         LayerMask layerMask(0);
//         layerMask.content = mask;
//         return layerMask;
//     }
//
//     unsigned int LayerMask::getMaskContent() const {
//         return content;
//     }
// } // isle_engine