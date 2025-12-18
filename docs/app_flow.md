# Flow of program


Assets of different types get `Imported` into the engine, stored raw as pointers.
These pointers are hidden in classes called PAssets. they are refcounted to ensure they are garbage collected properly.

The Asset Database has 4 actions:
- Read
- Write
- Update
- Delete.

It makes use of a utility 
```c++

    template<typename T>
    Ref<T> PAssetDatabase::queryDBForAsset(const QuerySpec<T>& spec, QueryOperation operation) {

        switch (operation)
        {
        case QueryOperation::Read:
            return performGetOperation(spec);
        case QueryOperation::Write:
            return performAddOperation(spec);
        case QueryOperation::Update:
            return performUpdateOperation(spec);
        case QueryOperation::Delete:
            return performDeleteOperation(spec);
        default:
            break;
        }
        return nullptr;
    }
```
to communicate with the Internals of the Asset Database.

Adding/Importing an asset will work thus:
```c++
template<typename T>
Ref<T> PAssetDatabase::performAddOperation(const QuerySpec<T>& spec)
{
    return spec.strategy->WriteOperation();
}
```

This reveals to us that every `spec` has a tye `T` attached to it. This is directly related to the type of Asset.
Each Asset thus has a way to read, write, update and delete it. Those methods are defined in what we call `Strategies`.

The Strategies are going to be type specific, in that we figure out their implemntation when we need an asset of that type in the engine.
>
> 1. For now though, we need to understand the data structure of every asset so that we dont keep changing code when we implement new strategies. 
> 2. Also, How do we ensure Query is standardised?
> 3. How do we serialize and deserialize assets after import?

These 3 questions are the obstacles that need be faced. They contain child questions but are the main issues on ground.

To progress, we need to setup the scene graph, fail at objects handling and serialization and then fix it.
This brings us to the dilemma of File Schema, especially `.pscene` files.