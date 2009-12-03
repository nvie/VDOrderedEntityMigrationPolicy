//
// VDOrderedEntityMigrationPolicy.m
// 
// General entity migration policy implementation for migrating Core Data entities
// that inherit from Brian Webster's BWOrderedManagedObject.
// 
// Created by Vincent Driessen.
// 
// Sources freely available at Github:
//   http://github.com/nvie/VDOrderedEntityMigrationPolicy
//

#import "VDOrderedEntityMigrationPolicy.h"
#import "BWOrderedManagedObject.h"


@implementation VDOrderedEntityMigrationPolicy


- (NSDictionary *)entityMappingForOrderedKeys {
	return [NSDictionary dictionary];
}


- (BOOL)createDestinationInstancesForSourceInstance:(NSManagedObject *)sInstance
									  entityMapping:(NSEntityMapping *)mapping
											manager:(NSMigrationManager *)manager
											  error:(NSError **)error {
	
	// Invoke super first
	if (![super createDestinationInstancesForSourceInstance:sInstance
											  entityMapping:mapping
													manager:manager
													  error:error]) {
		return NO;
	}
	
	// Set some shortcuts ('moc' and 'psc')
	NSManagedObjectContext *moc = [manager sourceContext];
	NSPersistentStoreCoordinator *psc = [moc persistentStoreCoordinator];
	
	// Then, for each ordered key, perform a URL migration
	NSDictionary *mappingForOrderedKeys = [self entityMappingForOrderedKeys];
	for (NSString *keyname in [mappingForOrderedKeys allKeys]) {
		
		// Create a mutable array to hold all instances from the source model this
		// ordered key refers to
		NSMutableArray *sourceInstances = [[NSMutableArray alloc] init];
		
		// Loop over all (source model) URL's that this ordered key refers to
		for (NSURL *url in (NSArray *)[sInstance valueForKey:keyname]) {
			NSManagedObjectID *objID = [psc managedObjectIDForURIRepresentation:url];
			NSManagedObject *object = [moc objectWithID:objID];
			[sourceInstances addObject:object];
		}
		
		// Query the migration manager for the corresponding instances from the
		// destination model
		NSArray *destinationInstances;
		destinationInstances = [manager destinationInstancesForEntityMappingNamed:[mappingForOrderedKeys objectForKey:keyname]
																  sourceInstances:sourceInstances];
		
		// Convert those destination instances back to URL's
		NSMutableArray *destinationURLs = [[NSMutableArray alloc] init];
		for (NSManagedObject *object in destinationInstances) {
			NSManagedObjectID *objID = [object objectID];
			NSURL *url = [objID URIRepresentation];
			[destinationURLs addObject:url];
		}
		
		// Get the object holding the ordered key's equivalent in the destination
		// object (as retreived from the manager's mapping).
		// We need this object to set the ordering on in the destination context.
		NSArray *orderedSourceInstanceList = [[NSArray alloc] initWithObjects:sInstance, nil];
		NSManagedObject *dInstance = [[manager destinationInstancesForEntityMappingNamed:[mapping name]
																		  sourceInstances:orderedSourceInstanceList]
										objectAtIndex:0];
		
		// Finally, we can set the new ordering onto the destination instance
		[dInstance setValue:destinationURLs forKey:keyname];
		
		// Free up memory
		[orderedSourceInstanceList release];
		[sourceInstances release];
		[destinationURLs release];
	}
	
	return YES;
}


@end
