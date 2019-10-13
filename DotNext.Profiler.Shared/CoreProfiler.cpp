#include "CoreProfiler.h"

HRESULT __stdcall CoreProfiler::QueryInterface(REFIID riid, void** ppvObject) {
	return E_NOTIMPL;
}

ULONG __stdcall CoreProfiler::AddRef(void) {
	return ++_refCount;
}

ULONG __stdcall CoreProfiler::Release(void) {
	auto count = --_refCount;
	if (count == 0)
		delete this;

	return count;
}

HRESULT CoreProfiler::Initialize(IUnknown* pICorProfilerInfoUnk) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::Shutdown() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::AppDomainCreationStarted(AppDomainID appDomainId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::AppDomainCreationFinished(AppDomainID appDomainId, HRESULT hrStatus) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::AppDomainShutdownStarted(AppDomainID appDomainId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::AppDomainShutdownFinished(AppDomainID appDomainId, HRESULT hrStatus) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::AssemblyLoadStarted(AssemblyID assemblyId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::AssemblyLoadFinished(AssemblyID assemblyId, HRESULT hrStatus) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::AssemblyUnloadStarted(AssemblyID assemblyId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::AssemblyUnloadFinished(AssemblyID assemblyId, HRESULT hrStatus) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ModuleLoadStarted(ModuleID moduleId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ModuleLoadFinished(ModuleID moduleId, HRESULT hrStatus) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ModuleUnloadStarted(ModuleID moduleId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ModuleUnloadFinished(ModuleID moduleId, HRESULT hrStatus) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ModuleAttachedToAssembly(ModuleID moduleId, AssemblyID AssemblyId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ClassLoadStarted(ClassID classId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ClassLoadFinished(ClassID classId, HRESULT hrStatus) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ClassUnloadStarted(ClassID classId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ClassUnloadFinished(ClassID classId, HRESULT hrStatus) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::FunctionUnloadStarted(FunctionID functionId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::JITCompilationStarted(FunctionID functionId, BOOL fIsSafeToBlock) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::JITCompilationFinished(FunctionID functionId, HRESULT hrStatus, BOOL fIsSafeToBlock) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::JITCachedFunctionSearchStarted(FunctionID functionId, BOOL* pbUseCachedFunction) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::JITCachedFunctionSearchFinished(FunctionID functionId, COR_PRF_JIT_CACHE result) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::JITFunctionPitched(FunctionID functionId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::JITInlining(FunctionID callerId, FunctionID calleeId, BOOL* pfShouldInline) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ThreadCreated(ThreadID threadId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ThreadDestroyed(ThreadID threadId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ThreadAssignedToOSThread(ThreadID managedThreadId, DWORD osThreadId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RemotingClientInvocationStarted() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RemotingClientSendingMessage(GUID* pCookie, BOOL fIsAsync) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RemotingClientReceivingReply(GUID* pCookie, BOOL fIsAsync) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RemotingClientInvocationFinished() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RemotingServerReceivingMessage(GUID* pCookie, BOOL fIsAsync) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RemotingServerInvocationStarted() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RemotingServerInvocationReturned() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RemotingServerSendingReply(GUID* pCookie, BOOL fIsAsync) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::UnmanagedToManagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ManagedToUnmanagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RuntimeSuspendStarted(COR_PRF_SUSPEND_REASON suspendReason) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RuntimeSuspendFinished() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RuntimeSuspendAborted() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RuntimeResumeStarted() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RuntimeResumeFinished() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RuntimeThreadSuspended(ThreadID threadId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RuntimeThreadResumed(ThreadID threadId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::MovedReferences(ULONG cMovedObjectIDRanges, ObjectID* oldObjectIDRangeStart, ObjectID* newObjectIDRangeStart, ULONG* cObjectIDRangeLength) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ObjectAllocated(ObjectID objectId, ClassID classId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ObjectsAllocatedByClass(ULONG cClassCount, ClassID* classIds, ULONG* cObjects) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ObjectReferences(ObjectID objectId, ClassID classId, ULONG cObjectRefs, ObjectID* objectRefIds) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RootReferences(ULONG cRootRefs, ObjectID* rootRefIds) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionThrown(ObjectID thrownObjectId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionSearchFunctionEnter(FunctionID functionId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionSearchFunctionLeave() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionSearchFilterEnter(FunctionID functionId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionSearchFilterLeave() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionSearchCatcherFound(FunctionID functionId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionOSHandlerEnter(UINT_PTR __unused) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionOSHandlerLeave(UINT_PTR __unused) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionUnwindFunctionEnter(FunctionID functionId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionUnwindFunctionLeave() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionUnwindFinallyEnter(FunctionID functionId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionUnwindFinallyLeave() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionCatcherEnter(FunctionID functionId, ObjectID objectId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionCatcherLeave() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::COMClassicVTableCreated(ClassID wrappedClassId, const GUID& implementedIID, void* pVTable, ULONG cSlots) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::COMClassicVTableDestroyed(ClassID wrappedClassId, const GUID& implementedIID, void* pVTable) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionCLRCatcherFound() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ExceptionCLRCatcherExecute() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ThreadNameChanged(ThreadID threadId, ULONG cchName, WCHAR* name) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::GarbageCollectionStarted(int cGenerations, BOOL* generationCollected, COR_PRF_GC_REASON reason) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::SurvivingReferences(ULONG cSurvivingObjectIDRanges, ObjectID* objectIDRangeStart, ULONG* cObjectIDRangeLength) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::GarbageCollectionFinished() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::FinalizeableObjectQueued(DWORD finalizerFlags, ObjectID objectID) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::RootReferences2(ULONG cRootRefs, ObjectID* rootRefIds, COR_PRF_GC_ROOT_KIND* rootKinds, COR_PRF_GC_ROOT_FLAGS* rootFlags, UINT_PTR* rootIds) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::HandleCreated(GCHandleID handleId, ObjectID initialObjectId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::HandleDestroyed(GCHandleID handleId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::InitializeForAttach(IUnknown* pCorProfilerInfoUnk, void* pvClientData, UINT cbClientData) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ProfilerAttachComplete() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ProfilerDetachSucceeded() {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ReJITCompilationStarted(FunctionID functionId, ReJITID rejitId, BOOL fIsSafeToBlock) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::GetReJITParameters(ModuleID moduleId, mdMethodDef methodId, ICorProfilerFunctionControl* pFunctionControl) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ReJITCompilationFinished(FunctionID functionId, ReJITID rejitId, HRESULT hrStatus, BOOL fIsSafeToBlock) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ReJITError(ModuleID moduleId, mdMethodDef methodId, FunctionID functionId, HRESULT hrStatus) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::MovedReferences2(ULONG cMovedObjectIDRanges, ObjectID* oldObjectIDRangeStart, ObjectID* newObjectIDRangeStart, SIZE_T* cObjectIDRangeLength) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::SurvivingReferences2(ULONG cSurvivingObjectIDRanges, ObjectID* objectIDRangeStart, SIZE_T* cObjectIDRangeLength) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ConditionalWeakTableElementReferences(ULONG cRootRefs, ObjectID* keyRefIds, ObjectID* valueRefIds, GCHandleID* rootIds) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::GetAssemblyReferences(const WCHAR* wszAssemblyPath, ICorProfilerAssemblyReferenceProvider* pAsmRefProvider) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::ModuleInMemorySymbolsUpdated(ModuleID moduleId) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::DynamicMethodJITCompilationStarted(FunctionID functionId, BOOL fIsSafeToBlock, LPCBYTE pILHeader, ULONG cbILHeader) {
	return E_NOTIMPL;
}

HRESULT CoreProfiler::DynamicMethodJITCompilationFinished(FunctionID functionId, HRESULT hrStatus, BOOL fIsSafeToBlock) {
	return E_NOTIMPL;
}
