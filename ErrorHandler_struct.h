#pragma once

#ifndef ERROR_HANDLER_STRUCT__H
#define ERROR_HANDLER_STRUCT__H
/* Deps */
#include <string>
#include <vector>

/* Structure */
struct ErrorHandler
{
	/*
		# Error Handler (struct)

		## Description
		An object which allows registering error-handling callback functions which 
		can be evoked when an issue arises.

		## Usage
		1. Create an ErrorHandler or a derived class of one.
		2. use the `registerErrorHandler()` method to register a new callback function, 
		   which will be invoked when an error arises.
		3. You can optionally, unregister one with `unregisterErrorHandler()`.
		4. When an error happens, call `onError()`.
		5. All set!
	*/

	/* Type Definitions */
	typedef void(*errorCallback)(const std::string& errorMessage);

	/* Elements */
	std::vector<errorCallback> errorHandlers;

	/* Methods */
	// Constructors & Destructor
	ErrorHandler()
	{
		this->errorHandlers.clear();
	};
	virtual ~ErrorHandler()
	{
		this->errorHandlers.clear();
	};

	// Callback Management
	inline void registerErrorHandler(errorCallback handler)
	{
		/*
			Adds an error handling function to the list of callbacks invoked when
			this ErrorHandler object is used to respond to an issue.
		*/
		this->errorHandlers.push_back(handler);
	};
	inline void unregisterErrorHandler(errorCallback handler)
	{
		/*
			Removes an error handler callback pointer from this ErrorHandler, so that 
			function won't be called when an error arises that this handler is used 
			to respond to.
		*/
		std::vector<errorCallback>::iterator itr = std::find(this->errorHandlers.begin(), this->errorHandlers.end(), handler);
		if ( itr != this->errorHandlers.end())
		{
			this->errorHandlers.erase(itr);
		};
	};

	// Error Handling
	inline void onError(const std::string& errorMessage) const
	{
		for (errorCallback handler : this->errorHandlers)
		{
			handler(errorMessage);
		};
	};
	inline void onError(const char* errorMessage) const
	{
		std::string msg = (std::string)errorMessage;
		this->onError(msg);
	};
};
#endif